///---------------------------- FILE HEADER ------------------------------------------------------
/// component   : QUANSER Q8 CARD
/// file        : quanser_Q8_driver.c
/// description : Implementation for the Q8 card utility I/O functions and registration of these                 
///               functions within rtdm.
/// author      : Egemen Kaleli - EK
///
/// date        : july-2008
///
///------------------------------------------------------------------------------------------------

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/pci.h>
#include <linux/vmalloc.h>
#include <asm/io.h>
#include <linux/ioport.h>
#include <linux/kdev_t.h>
#include <linux/cdev.h>
#include <asm/uaccess.h>
#include <linux/capability.h>
#include <linux/sched.h>
#include <rtdm/rtdm_driver.h>
#include "q8driver.h"


/**
 * module info
 */
MODULE_DESCRIPTION("RTDM driver for Q8");
MODULE_AUTHOR("Egemen Kaleli-EK,Robotics and Control Technologies Laboratory@GYTE");
MODULE_LICENSE("GPL");

int Q8_rt_rw(struct rtdm_dev_context *,rtdm_user_info_t*,void*,size_t);

/**
 * global variables
 */
int first_loop=0;
int ret_loop_val=0;
/**
 * define devices our driver supports
 */
static struct pci_device_id    QUANSER_ids[]={
  {PCI_DEVICE(Q8_VENDOR_ID_QUANSER,Q8_DEVICE_ID)},
  {0,},
};

MODULE_DEVICE_TABLE (pci, QUANSER_ids);


 static struct pci_driver quanser_Q8_driver = {
     .name     = DRV_NAME,
     .id_table = QUANSER_ids,
     .probe  = Q8_probe,
     .remove = Q8_remove,/*__devexit_p*/
  };

 struct xen_Q8_context{
  /* address in kernel space (virtual memory) */
     void __iomem       *base_address;
  /* physical address */
     unsigned long      location;
  /* size/length of the memory */
     unsigned long      mem_size;
     struct rtdm_device *xen_device;
     int                dev_id;
        uint8_t           irq_line;
     struct tagQ8Registers* Q8reg;        
  };

   struct xen_Q8_context xen_Q8_struct;
   struct xen_Q8_context *q8Con = &xen_Q8_struct;

   #include "Q8config.h"
///========================== FUNCTION HEADER =========================================================================
/// Name        : xen_Q8_rt_open
/// Input       : context   -RTDM API
///               user_info -RTDM API
///               oflags    -RTDM API
/// Output      : None
/// Return      : an integer value(not used)
/// Description : This function is nıt dong anything useful.I have taken this from a weblink on                
///               www.xenomai.org(http://stud3.tuwien.ac.at). It is called when the device is opened.                  
///=====================================================================================================================


int xen_Q8_rt_open(struct rtdm_dev_context    *context,
                          rtdm_user_info_t    *user_info,
                          int                 oflags)
{
     struct xen_Q8_context *my_context;
     int dev_id = context->device->device_id;
     my_context = (struct xen_Q8_context *)context->dev_private;
     my_context->dev_id = dev_id;
    rtdm_printk( KERN_DEBUG "opening dev with id:%d\n", my_context->dev_id);
  return 0;
}
///========================== FUNCTION HEADER =========================================================================
/// Name        : xen_Q8_rt_close
/// Input       : context   -RTDM API
///               user_info -RTDM API
///               oflags    -RTDM API
/// Output      : None
/// Return      : an integer value(not used)
/// Description : I have taken this from a weblink on  www.xenomai.org(http://stud3.tuwien.ac.at) .
///               It is called when the device is closed.                                             
///                                      
///                        
///=====================================================================================================================

int xen_Q8_rt_close(struct rtdm_dev_context   *context,
                    rtdm_user_info_t          *user_info)
{
     struct xen_Q8_context *my_context;
  // get the context struct
     my_context = (struct xen_Q8_context *)context->dev_private;
     printk( KERN_DEBUG "closing... id of dev is %d\n", my_context->dev_id);
     iowrite32(0x08000800,q8Con->base_address+0x40);//"0 V",registerA(channel 04)
     iowrite32(0x08000800,q8Con->base_address+0x44);//  "  ,registerB(channel 15) 
     iowrite32(0x08000800,q8Con->base_address+0x48);//  "  ,registerC(channel 26)
     iowrite32(0x08000800,q8Con->base_address+0x4C);//  "  ,registerD(channel 37)
     iowrite32(0x08000800,q8Con->base_address+0x50);
     return 0;
}
/**********************************************************/
/*            DRIVER OPERATIONS                           */
/**********************************************************/
static const struct rtdm_device xen_Q8_driver = {
  struct_version:     RTDM_DEVICE_STRUCT_VER,
  device_flags:       RTDM_NAMED_DEVICE | RTDM_EXCLUSIVE,
  context_size:       sizeof(struct xen_Q8_context),
  device_name:        "", 
  open_rt:          xen_Q8_rt_open,
  open_nrt:         xen_Q8_rt_open,
  ops: {
    close_rt:       xen_Q8_rt_close,
    close_nrt:      xen_Q8_rt_close,
    ioctl_rt:       NULL,
    ioctl_nrt:      NULL,
    read_rt:        Q8_rt_rw,
    read_nrt:       Q8_rt_rw,
    write_rt:       Q8_rt_rw,
    write_nrt:      Q8_rt_rw,
  },
  device_class:       RTDM_CLASS_SERIAL,
  device_sub_class:   0, 
  driver_name:        DRV_NAME, 
  peripheral_name:    "QUANSER_Q8 I/0 BOARD",                                   
  provider_name:      "GYTE ROBOT LAB",
};

///========================== FUNCTION HEADER =========================================================================
/// Name        : Q8_Counter_Output
/// Input       : cardNum - 
///               user_info  -
///               buf        -
/// Output      : None
/// Return      : an integer value(not used)
/// Description : This function is used to generate square wave output.In additon,clock source can be selected using this function.
///=====================================================================================================================
int Q8_Counter_Output(int cardNum,rtdm_user_info_t* user_info,void* buf)
{
  struct_Q8_Config q8Str;
  if(rtdm_safe_copy_from_user(user_info, &q8Str,buf, sizeof(struct_Q8_Config)))
    return -EFAULT;
 switch(q8Str.iClockSource)
 {
     case COUNTER : 
        iowrite32(q8Str.udwPeriod,&(q8Con->Q8reg->counter.sq.preload));//ok  
         countercontrol=(countercontrol & 0x00000000) | CCTRL_CNTREN | CCTRL_CNTROUTEN;
         iowrite32(countercontrol ,&(q8Con->Q8reg->counterControl));
         iowrite32(countercontrol | CCTRL_CNTRLD | CCTRL_CNTRVAL,&(q8Con->Q8reg->counterControl));
        break;
       case WATCHDOG:
        iowrite32(q8Str.udwPeriod,&(q8Con->Q8reg->watchdog.sq.preload));
        countercontrol=(countercontrol & 0x00000000L) | CCTRL_WDOGEN | CCTRL_WDOGOUTEN | CCTRL_WDOGSEL ;
        iowrite32( countercontrol,&(q8Con->Q8reg->counterControl));
        iowrite32(countercontrol  | CCTRL_WDOGLD | CCTRL_WDOGVAL ,&(q8Con->Q8reg->counterControl));
      break;
       default:
     break;
 }
 return 0;
}
///========================== FUNCTION HEADER =========================================================================
/// Name        : Q8_PWM_Output
/// Input       : cardNum - PCI memory region that is mapped to Q8 card memory  
///               user_info  - RTDM driver
///               buf        -
/// Output      : None
/// Return      : an integer value(not used)
/// Description : This function is used to generate PWM output.In additon,clock source can be selected using this function.
///=====================================================================================================================

int Q8_PWM_Output(int cardNum,rtdm_user_info_t* user_info,void* buf){
struct_Q8_Config q8Str;
if(rtdm_safe_copy_from_user(user_info, &q8Str,buf,sizeof(struct_Q8_Config))){
return -EFAULT;
}
switch(q8Str.iClockSource)
{
 /*iowrite32(q8Str.udwPeriod,&(q8Con->Q8reg->counter.sq.preload));//ok  
         countercontrol=(countercontrol & 0x0000ffff) | CCTRL_CNTREN | CCTRL_CNTROUTEN;
         iowrite32(countercontrol ,&(q8Con->Q8reg->counterControl));
         iowrite32(countercontrol | CCTRL_CNTRLD | CCTRL_CNTRVAL,&(q8Con->Q8reg->counterControl));*/
   case COUNTER :
    countercontrol= (countercontrol & 0x0000ffff) | CCTRL_CNTRMODE | CCTRL_CNTREN | CCTRL_CNTROUTEN;
   iowrite32(countercontrol ,&(q8Con->Q8reg->counterControl));//PWM MODE
   iowrite32((q8Str.udwLow),&(q8Con->Q8reg->counter.pwm.preloadLow));
   iowrite32((q8Str.udwHigh),&(q8Con->Q8reg->counter.pwm.preloadHigh));
   iowrite32(countercontrol | CCTRL_CNTRLD | CCTRL_CNTRVAL ,&(q8Con->Q8reg->counterControl));
    break;
   case WATCHDOG:
   countercontrol=(countercontrol & 0xffff0000) | CCTRL_WDOGMODE | CCTRL_WDOGEN | CCTRL_WDOGOUTEN | CCTRL_WDOGSEL;
   iowrite32(countercontrol ,&(q8Con->Q8reg->counterControl));
   iowrite32(q8Str.udwLow ,&(q8Con->Q8reg->watchdog.pwm.preloadLow));
   iowrite32(q8Str.udwHigh,&(q8Con->Q8reg->watchdog.pwm.preloadHigh));
   iowrite32(countercontrol | CCTRL_WDOGLD | CCTRL_WDOGVAL,&(q8Con->Q8reg->counterControl));
   break;
   default:
   break;
}
return 0;
}
///========================== FUNCTION HEADER =========================================================================
/// Name        : Q8_PWM_Output
/// Input       : cardNum - PCI memory region that is mapped to Q8 card memory  
///               user_info  - RTDM driver
///               buf        - User memory region adress. 
/// Output      : None
/// Return      : an integer value(not used)
/// Description : This function is used to activate and watchdog timer .In additon,clock source can be selected using             this function.
///=====================================================================================================================


int Q8_Watchdog_Timer(int cardNum,rtdm_user_info_t* user_info,void* buf ){
struct_Q8_Config q8Str;
if(rtdm_safe_copy_from_user(user_info, &q8Str,buf,sizeof(struct_Q8_Config))){
   return -EFAULT;
}
   iowrite32(q8Str.udwPeriod,&(q8Con->Q8reg->watchdog.sq.preload));
   countercontrol=(countercontrol & 0x0000ffff)|CCTRL_WDOGEN | CCTRL_WDOGACT | CCTRL_WDOGOUTEN;
   iowrite32(countercontrol ,&(q8Con->Q8reg->counterControl));
   iowrite32(countercontrol | CCTRL_WDOGLD | CCTRL_WDOGVAL ,&(q8Con->Q8reg->counterControl));
   return 0;
}
///========================== FUNCTION HEADER =========================================================================
/// Name        : Q8_Digital_Config
/// Input       : cardNum    - PCI memory region that is mapped to Q8 card memory  
///               user_info  - RTDM driver
///               buf        - User memory region adress. 
/// Output      : None
/// Return      : an integer value(not used)
/// Description : This function configures the specified bit channels.

///=====================================================================================================================





///========================== FUNCTION HEADER =========================================================================
/// Name        : Q8_Digital_Output
/// Input       : cardNum    - PCI memory region that is mapped to Q8 card memory  
///               user_info  - RTDM driver
///               buf        - User memory region adress. 
/// Output      : None
/// Return      : an integer value(not used)
/// Description : This function writes a desired value to the specified bit channels.
///=====================================================================================================================
int Q8_Digital_Output(int cardNum,rtdm_user_info_t* user_info,void* buf){

struct_Q8_Config q8Str;

uint32_T directionPrevious= ioread32(&(q8Con->Q8reg->digitalDirection));


if(rtdm_safe_copy_from_user(user_info, &q8Str,buf, sizeof(struct_Q8_Config))){
   return -EFAULT;
}


if(q8Str. onlyDigitalData== -1){

iowrite32(q8Str.udwDataRegister,&(q8Con->Q8reg->digitalIO));
return 0;

}



/* Explaination: q8Str.udwDataDirection yazmacı user fonksiyonu içerisinde düzenlenmeli. Bu yazmaçta output bitleri "1",diğerleri "0"
değerine sahip olmalı*/
else{
directionPrevious |= q8Str.udwDataDirection;

   
   iowrite32(directionPrevious,&(q8Con->Q8reg->digitalDirection));//channel selection;
   iowrite32(q8Str.udwDataRegister,&(q8Con->Q8reg->digitalIO));
   return 0;}
}
///========================== FUNCTION HEADER =========================================================================
/// Name        : Q8_Digital_Input
/// Input       : cardNum    - PCI memory region that is mapped to Q8 card memory  
///               user_info  - RTDM driver
///               buf        - User memory region adress. 
/// Output      : None
/// Return      : an integer value(not used)
/// Description : This function reads a the specified bit channels.
///=====================================================================================================================
int Q8_Digital_Input(int cardNum,rtdm_user_info_t* user_info,void* buf){


struct_Q8_Config q8Str;

uint32_T directionPrevious= ioread32(&(q8Con->Q8reg->digitalDirection));
 
if(rtdm_safe_copy_from_user(user_info, &q8Str,buf,sizeof(struct_Q8_Config))){
   return -EFAULT;
}



if(q8Str. onlyDigitalData== -1)
{
q8Str.udwDataRegister=ioread32(&(q8Con->Q8reg->digitalIO));
   if(rtdm_safe_copy_to_user(user_info,buf, &q8Str, sizeof(struct_Q8_Config)))           
      return -EFAULT;

}


/* Explaination: q8Str.udwDataDirection yazmacı user fonksiyonu içerisinde düzenlenmeli. Bu yazmaçta input bitleri "0",diğerleri "1"
değerine sahip olmalı*/

//directionPrevious &= q8Str.udwDataDirection;
else{
   iowrite32(directionPrevious,&(q8Con->Q8reg->digitalDirection));//channel selection;
//iowrite32(0x00000000,&(q8Con->Q8reg->digitalDirection));
   q8Str.udwDataRegister=ioread32(&(q8Con->Q8reg->digitalIO));
   if(rtdm_safe_copy_to_user(user_info,buf, &q8Str, sizeof(struct_Q8_Config)))           
      return -EFAULT;
}
return 1;

}
///========================== FUNCTION HEADER ===================================================
/// Name        : Q8_DAC0_WRITE
/// Input       : cardNum  - PCI memory region that is mapped to Q8 card memory  
///               user_info- RTDM user information
///               buf      - USER memory region 
/// Output      : None
/// Return      : an integer value(not used)
/// Description : This function is used to output voltage to the specified DA
///               channel
///==============================================================================================
int Q8_DAC0_WRITE(int cardNum,rtdm_user_info_t* user_info,void* buf){
struct_Q8_Config q8Str;
if(rtdm_safe_copy_from_user(user_info,&q8Str,buf,sizeof(struct_Q8_Config))){
   return -EFAULT;
}
   iowrite16(q8Str.uwValueUnsigned,&(q8Con->Q8reg->analogOutput.one.dac0));//value_write
   iowrite32(0x00000000,&(q8Con->Q8reg->analogUpdate.all));
   return 0;
}
///========================== FUNCTION HEADER ===================================================
/// Name        : Q8_DAC1_WRITE
/// Input       : cardNum  - PCI memory region that is mapped to Q8 card memory  
///               user_info- RTDM user information
///               buf      - USER memory region 
/// Output      : None
/// Return      : an integer value(not used)
/// Description : This function is used to output voltage to the specified DA
///               channel
///==============================================================================================
int Q8_DAC1_WRITE(int cardNum,rtdm_user_info_t* user_info,void* buf){
struct_Q8_Config q8Str;
   if(rtdm_safe_copy_from_user(user_info, &q8Str,buf,sizeof(struct_Q8_Config))){
      return -EFAULT;
   }
   iowrite16(q8Str.uwValueUnsigned,&(q8Con->Q8reg->analogOutput.one.dac1));
   iowrite32(0x00000000,q8Con->base_address+0x50);
   return 0;
}
///========================== FUNCTION HEADER ===================================================
/// Name        : Q8_DAC2_WRITE
/// Input       : cardNum  - PCI memory region that is mapped to Q8 card memory  
///               user_info- RTDM user information
///               buf      - USER memory region     -
/// Output      : None
/// Return      : an integer value(not used)
/// Description : This function is used to output voltage to the specified DA
///               channel
///==============================================================================================
int Q8_DAC2_WRITE(int cardNum,rtdm_user_info_t* user_info,void* buf){
struct_Q8_Config q8Str;
   if(rtdm_safe_copy_from_user(user_info, &q8Str,buf,sizeof(struct_Q8_Config))){
      return -EFAULT;
   }
    iowrite16(q8Str.uwValueUnsigned,&(q8Con->Q8reg->analogOutput.one.dac2));
    iowrite32(0x00000000,q8Con->base_address+0x50);
   return 0;
}
///========================== FUNCTION HEADER ===================================================
/// Name        : Q8_DAC3_WRITE
/// Input       : cardNum  - PCI memory region that is mapped to Q8 card memory  
///               user_info- RTDM user information
///               buf      - USER memory region    
/// Output      : None
/// Return      : an integer value(not used)
/// Description : This function is used to output voltage to the specified DA
///               channel
///==============================================================================================
int Q8_DAC3_WRITE(int cardNum,rtdm_user_info_t* user_info,void* buf){
   struct_Q8_Config q8Str;
   if(rtdm_safe_copy_from_user(user_info, &q8Str,buf, sizeof(struct_Q8_Config))){
      return -EFAULT;
   }
      iowrite16(q8Str.uwValueUnsigned,&(q8Con->Q8reg->analogOutput.one.dac3));//erase if...
      iowrite32(0x00000000,q8Con->base_address+0x50);
      return 0;
}
///========================== FUNCTION HEADER ===================================================
/// Name        : Q8_DAC4_WRITE
/// Input       : cardNum  - PCI memory region that is mapped to Q8 card memory  
///               user_info- RTDM user information
///               buf      - USER memory region 
/// Output      : None
/// Return      : an integer value(not used)
/// Description : This function is used to output voltage to the specified DA
///               channel
///==============================================================================================
int Q8_DAC4_WRITE(int cardNum,rtdm_user_info_t* user_info,void* buf){
   struct_Q8_Config q8Str;
   if(rtdm_safe_copy_from_user(user_info, &q8Str,buf,sizeof(struct_Q8_Config))){
      return -EFAULT;
   }
    iowrite16(q8Str.uwValueUnsigned,&(q8Con->Q8reg->analogOutput.one.dac4));//erase if...        
    iowrite32(0,&(q8Con->Q8reg->analogUpdate.all));
       return 0;
}
///========================== FUNCTION HEADER ===================================================
/// Name        : Q8_DAC5_WRITE
/// Input       : cardNum  - PCI memory region that is mapped to Q8 card memory  
///               user_info- RTDM user information
///               buf      - USER memory region 
/// Output      : None
/// Return      : an integer value(not used)
/// Description : This function is used to output voltage to the specified DA
///               channel
///==============================================================================================
int Q8_DAC5_WRITE(int cardNum,rtdm_user_info_t* user_info,void* buf){
    struct_Q8_Config q8Str;
    if(rtdm_safe_copy_from_user(user_info, &q8Str,buf , sizeof(struct_Q8_Config))){
      return -EFAULT;
   }
        iowrite16(q8Str.uwValueUnsigned,&(q8Con->Q8reg->analogOutput.one.dac5));//erase if...
        iowrite32(0x00000000,q8Con->base_address+0x50);
   return 0;
}
///========================== FUNCTION HEADER ===================================================
/// Name        : Q8_DAC6_WRITE
/// Input       : cardNum  - PCI memory region that is mapped to Q8 card memory  
///               user_info- RTDM user information
///               buf      - USER memory region 
/// Output      : None
/// Return      : an integer value(not used)
/// Description : This function is used to output voltage to the specified DA
///               channel
///==============================================================================================
int Q8_DAC6_WRITE(int cardNum,rtdm_user_info_t* user_info,void* buf){
    struct_Q8_Config q8Str;
   if(rtdm_safe_copy_from_user(user_info, &q8Str,buf,sizeof(struct_Q8_Config))){
   return -EFAULT;
   }
   iowrite16(q8Str.uwValueUnsigned,&(q8Con->Q8reg->analogOutput.one.dac6));//erase if...
   iowrite32(0x00000000,q8Con->base_address+0x50);
   return 0;
}
///========================== FUNCTION HEADER ===================================================
/// Name        : Q8_DAC7_WRITE
/// Input       : cardNum  - PCI memory region that is mapped to Q8 card memory  
///               user_info- RTDM user information
///               buf      - USER memory region 
/// Output      : None
/// Return      : an integer value(not used)
/// Description : This function is used to output voltage to the specified DA
///               channel
///==============================================================================================
int Q8_DAC7_WRITE(int cardNum,rtdm_user_info_t* user_info,void* buf){
   struct_Q8_Config q8Str;
   if(rtdm_safe_copy_from_user(user_info, &q8Str,buf,sizeof(struct_Q8_Config))){
   return -EFAULT;
}
        iowrite16(q8Str.uwValueUnsigned,&(q8Con->Q8reg->analogOutput.one.dac7));//erase if...
        iowrite32(0x00000000, q8Con->base_address+0x50);
   return 0;
}
///========================== FUNCTION HEADER =============================================================
/// Name        : Q8_ADC0_READ
/// Input       : cardNum  - PCI memory region that is mapped to Q8 card memory  
///               user_info- RTDM user information
///               buf      - USER memory region 
/// Output      : None
/// Return      : an integer value(not used)
/// Description : This function is used to read the input voltage  from the specified channel
///               
///========================================================================================================
int Q8_ADC0READ(int cardNum,rtdm_user_info_t* user_info,void* buf){
   struct_Q8_Config q8Str;
   iowrite32(0x00000001,&(q8Con->Q8reg->analogInput.select));
   iowrite32(cntrl | 0x00008000,&(q8Con->Q8reg->control));
   while(!(ioread32(&(q8Con->Q8reg->status)) & STAT_ADC03RDY));
   q8Str.wValueSigned=ioread16(&(q8Con->Q8reg->analogInput.one.adc03));
   if(rtdm_safe_copy_to_user(user_info,buf, &q8Str, sizeof(struct_Q8_Config)))        
   return -EFAULT;
   return 0;
}

///========================== FUNCTION HEADER =============================================================
/// Name        : Q8_ADC1_READ
/// Input       : cardNum  - PCI memory region that is mapped to Q8 card memory  
///               user_info- RTDM user information
///               buf      - USER memory region 
/// Output      : None
/// Return      : an integer value(not used)
/// Description : This function is used to read the input voltage  from the specified channel
///               
///========================================================================================================
int Q8_ADC1READ(int cardNum,rtdm_user_info_t* user_info,void* buf){
   struct_Q8_Config q8Str;
   iowrite32(0x00000002,&(q8Con->Q8reg->analogInput.select));
   iowrite32(cntrl | 0x00008000,&(q8Con->Q8reg->control));
   while(!(ioread32(&(q8Con->Q8reg->status)) & STAT_ADC03RDY));
   q8Str.wValueSigned=ioread16(&(q8Con->Q8reg->analogInput.one.adc03));
   if(rtdm_safe_copy_to_user(user_info,buf, &q8Str, sizeof(struct_Q8_Config)))
   return -EFAULT;
   return 0;
}

///========================== FUNCTION HEADER =============================================================
/// Name        : Q8_ADC2_READ
/// Input       : cardNum  - PCI memory region that is mapped to Q8 card memory  
///               user_info- RTDM user information
///               buf      - USER memory region 
/// Output      : None
/// Return      : an integer value(not used)
/// Description : This function is used to read the input voltage  from the specified channel
///               
///========================================================================================================
int Q8_ADC2READ(int cardNum,rtdm_user_info_t* user_info,void* buf){
   struct_Q8_Config q8Str;
   iowrite32(0x00000004,&(q8Con->Q8reg->analogInput.select));
   iowrite32(cntrl | 0x00008000,&(q8Con->Q8reg->control));
   while(!(ioread32(&(q8Con->Q8reg->status)) & STAT_ADC03RDY));
   q8Str.wValueSigned=ioread16(&(q8Con->Q8reg->analogInput.one.adc03));
   if(rtdm_safe_copy_to_user(user_info,buf, &q8Str, sizeof(struct_Q8_Config)))            
   return -EFAULT;     
   return 0;
}
///========================== FUNCTION HEADER =============================================================
/// Name        : Q8_ADC3_READ
/// Input       : cardNum  - PCI memory region that is mapped to Q8 card memory  
///               user_info- RTDM user information
///               buf      - USER memory region 
/// Output      : None
/// Return      : an integer value(not used)
/// Description : This function is used to read the input voltage  from the specified channel
///               
///========================================================================================================
int Q8_ADC3READ(int cardNum,rtdm_user_info_t* user_info,void* buf){
   struct_Q8_Config q8Str;
   iowrite32(0x00000008,&(q8Con->Q8reg->analogInput.select));
   iowrite32(cntrl | 0x00008000,&(q8Con->Q8reg->control));
   while(!(ioread32(&(q8Con->Q8reg->status)) & STAT_ADC03RDY));
   q8Str.wValueSigned=ioread16(&(q8Con->Q8reg->analogInput.one.adc03));
   if(rtdm_safe_copy_to_user(user_info,buf, &q8Str, sizeof(struct_Q8_Config)))           
   return -EFAULT;
   return 0;
}
///========================== FUNCTION HEADER =============================================================
/// Name        : Q8_ADC4_READ
/// Input       : cardNum  - PCI memory region that is mapped to Q8 card memory  
///               user_info- RTDM user information
///               buf      - USER memory region 
/// Output      : None
/// Return      : an integer value(not used)
/// Description : This function is used to read the input voltage  from the specified channel
///               
///========================================================================================================
int Q8_ADC4READ(int cardNum,rtdm_user_info_t* user_info,void* buf){
   struct_Q8_Config q8Str;
   iowrite32(0x00010000,&(q8Con->Q8reg->analogInput.select));
   iowrite32(cntrl | 0x00800000,&(q8Con->Q8reg->control));
   while(!(ioread32(&(q8Con->Q8reg->status)) & STAT_ADC47RDY));
   q8Str.wValueSigned=ioread16(&(q8Con->Q8reg->analogInput.one.adc47));
   if(rtdm_safe_copy_to_user(user_info,buf, &q8Str, sizeof(struct_Q8_Config)))
   return -EFAULT;
   return 0;
}
///========================== FUNCTION HEADER =============================================================
/// Name        : Q8_ADC5_READ
/// Input       : cardNum  - PCI memory region that is mapped to Q8 card memory  
///               user_info- RTDM user information
///               buf      - USER memory region 
/// Output      : None
/// Return      : an integer value(not used)
/// Description : This function is used to read the input voltage  from the specified channel
///               
///========================================================================================================
int Q8_ADC5READ(int cardNum,rtdm_user_info_t* user_info,void* buf){
   struct_Q8_Config q8Str;
   iowrite32(0x00020000,&(q8Con->Q8reg->analogInput.select));
   iowrite32(cntrl | 0x00800000,&(q8Con->Q8reg->control));
   while(!(ioread32(&(q8Con->Q8reg->status)) & STAT_ADC47RDY));
   q8Str.wValueSigned=ioread16(&(q8Con->Q8reg->analogInput.one.adc47));
   if(rtdm_safe_copy_to_user(user_info,buf,&q8Str, sizeof(struct_Q8_Config)))
   return -EFAULT;         
   return 0;
}
///========================== FUNCTION HEADER =============================================================
/// Name        : Q8_ADC6_READ
/// Input       : cardNum  - PCI memory region that is mapped to Q8 card memory  
///               user_info- RTDM user information
///               buf      - USER memory region 
/// Output      : None
/// Return      : an integer value(not used)
/// Description : This function is used to read the input voltage  from the specified channel
///               
///========================================================================================================
int Q8_ADC6READ(int cardNum,rtdm_user_info_t* user_info,void* buf){
   struct_Q8_Config q8Str;
   iowrite32(0x00040000,&(q8Con->Q8reg->analogInput.select));
   iowrite32(cntrl | 0x00800000,&(q8Con->Q8reg->control));
   while(!(ioread32(&(q8Con->Q8reg->status)) & STAT_ADC47RDY));
   q8Str.wValueSigned=ioread16(&(q8Con->Q8reg->analogInput.one.adc47));
   if(rtdm_safe_copy_to_user(user_info,buf, &q8Str, sizeof(struct_Q8_Config)))  
   return -EFAULT;
   return 0;
}
///========================== FUNCTION HEADER =============================================================
/// Name        : Q8_ADC7_READ
/// Input       : cardNum  - PCI memory region that is mapped to Q8 card memory  
///               user_info- RTDM user information
///               buf      - USER memory region 
/// Output      : None
/// Return      : an integer value(not used)
/// Description : This function is used to read the input voltage  from the specified channel
///               
///========================================================================================================
int Q8_ADC7READ(int cardNum,rtdm_user_info_t* user_info,void* buf){
   struct_Q8_Config q8Str;
   iowrite32(0x00080000,&(q8Con->Q8reg->analogInput.select));
   iowrite32(cntrl | 0x00800000,&(q8Con->Q8reg->control));
   while(!(ioread32(&(q8Con->Q8reg->status)) & STAT_ADC47RDY));
   q8Str.wValueSigned=ioread16(&(q8Con->Q8reg->analogInput.one.adc47));
   if(rtdm_safe_copy_to_user(user_info,buf,&q8Str, sizeof(struct_Q8_Config)))          
   return -EFAULT;
   return 0;
}
///========================== FUNCTION HEADER =============================================================
/// Name        : Q8_ENC0_READ
/// Input       : cardNum  - PCI memory region that is mapped to Q8 card memory  
///               user_info- RTDM user information
///               buf      - USER memory region 
/// Output      : None
/// Return      : an integer value(not used)
/// Description : This function is used to read the encoder counter value  from the specified channel
///               
///========================================================================================================
int Q8_ENC0_READ(int cardNum,rtdm_user_info_t* user_info,void* buf){
   struct_Q8_Config q8Str;
   int8_t nMSB;
   uint8_t nISB;
   uint8_t nLSB;
   iowrite8(ENC_ONE_CHANNEL | ENC_RLD_REGISTER | ENC_RLD_GET_CNTR | ENC_RLD_RESET_BP,
                            &(q8Con->Q8reg->encoderControl.one.enc0));
   nLSB=ioread8(&(q8Con->Q8reg->encoderData.one.enc0));
      nISB=ioread8(&(q8Con->Q8reg->encoderData.one.enc0));
      nMSB=ioread8(&(q8Con->Q8reg->encoderData.one.enc0));
     q8Str.dwNvalue=(nMSB << 16) | (nISB << 8) | nLSB;
       if(rtdm_safe_copy_to_user(user_info,buf,&q8Str,sizeof(struct_Q8_Config)))
        return -EFAULT;
   else 
        return 0;
}
///========================== FUNCTION HEADER ==========================================================================
/// Name        : Q8_ENC1_READ
/// Input       : cardNum  - PCI memory region that is mapped to Q8 card memory  
///               user_info- RTDM user information
///               buf      - USER memory region 
/// Output      : None
/// Return      : an integer value(not used)
/// Description : This function is used to read the encoder counter value  from the specified channel
///               
///=====================================================================================================================
int Q8_ENC1_READ(int cardNum,rtdm_user_info_t* user_info,void* buf){
      struct_Q8_Config q8Str;
   int8_t nMSB;
   uint8_t nISB;
   uint8_t nLSB;
      iowrite8(ENC_ONE_CHANNEL | ENC_RLD_REGISTER | ENC_RLD_GET_CNTR | ENC_RLD_RESET_BP,
                            &(q8Con->Q8reg->encoderControl.one.enc1));
      nLSB=ioread8(&(q8Con->Q8reg->encoderData.one.enc1));
      nISB=ioread8(&(q8Con->Q8reg->encoderData.one.enc1));
      nMSB=ioread8(&(q8Con->Q8reg->encoderData.one.enc1));
       q8Str.dwNvalue=(nMSB << 16) | (nISB << 8) | nLSB;
       if(rtdm_safe_copy_to_user(user_info,buf,&q8Str,sizeof(struct_Q8_Config)))
        return -EFAULT;
      else 
       return 0; 
}
///========================== FUNCTION HEADER =============================================================
/// Name        : Q8_ENC2_READ
/// Input       : cardNum  - PCI memory region that is mapped to Q8 card memory  
///               user_info- RTDM user information
///               buf      - USER memory region 
/// Output      : None
/// Return      : an integer value(not used)
/// Description : This function is used to read the encoder counter value  from the specified channel
///               
///========================================================================================================
int Q8_ENC2_READ(int cardNum,rtdm_user_info_t* user_info,void* buf){
       struct_Q8_Config q8Str;
   int8_t nMSB;
   uint8_t nISB;
   uint8_t nLSB;
   iowrite8(ENC_ONE_CHANNEL | ENC_RLD_REGISTER | ENC_RLD_GET_CNTR | ENC_RLD_RESET_BP,
                            &(q8Con->Q8reg->encoderControl.one.enc2));
        nLSB=ioread8(&(q8Con->Q8reg->encoderData.one.enc2));
      nISB=ioread8(&(q8Con->Q8reg->encoderData.one.enc2));
      nMSB=ioread8(&(q8Con->Q8reg->encoderData.one.enc2));
   q8Str.dwNvalue=(nMSB << 16) | (nISB << 8) | nLSB;
       if(rtdm_safe_copy_to_user(user_info,buf,&q8Str,sizeof(struct_Q8_Config)))
        return -EFAULT;
      else 
     return 0;
}
///========================== FUNCTION HEADER =============================================================
/// Name        : Q8_ENC3_READ
/// Input       : cardNum  - PCI memory region that is mapped to Q8 card memory  
///               user_info- RTDM user information
///               buf      - USER memory region 
/// Output      : None
/// Return      : an integer value(not used)
/// Description : This function is used to read the encoder counter value  from the specified channel
///               
///========================================================================================================
int Q8_ENC3_READ(int cardNum,rtdm_user_info_t* user_info,void* buf){
       struct_Q8_Config q8Str;
   int8_t  nMSB;
   uint8_t nISB;
   uint8_t nLSB;
   iowrite8(ENC_ONE_CHANNEL | ENC_RLD_REGISTER | ENC_RLD_GET_CNTR | ENC_RLD_RESET_BP,
                 &(q8Con->Q8reg->encoderControl.one.enc3));
   nLSB=ioread8(&(q8Con->Q8reg->encoderData.one.enc3));
   nISB=ioread8(&(q8Con->Q8reg->encoderData.one.enc3));
      nMSB=ioread8(&(q8Con->Q8reg->encoderData.one.enc3));
    
       q8Str.dwNvalue=(nMSB << 16) | (nISB << 8) | nLSB;
       if(rtdm_safe_copy_to_user(user_info,buf,&q8Str,sizeof(struct_Q8_Config)))
            return -EFAULT;
   else 
     return 0;
}
///========================== FUNCTION HEADER =============================================================
/// Name        : Q8_ENC4_READ
/// Input       : cardNum  - PCI memory region that is mapped to Q8 card memory  
///               user_info- RTDM user information
///               buf      - USER memory region 
/// Output      : None
/// Return      : an integer value(not used)
/// Description : This function is used to read the encoder counter value  from the specified channel
///               
///========================================================================================================
int Q8_ENC4_READ(int cardNum,rtdm_user_info_t* user_info,void* buf){
       struct_Q8_Config q8Str;
   int8_t  nMSB;
   uint8_t nISB;
   uint8_t nLSB;
      iowrite8(ENC_ONE_CHANNEL | ENC_RLD_REGISTER | ENC_RLD_GET_CNTR | ENC_RLD_RESET_BP,
                            &(q8Con->Q8reg->encoderControl.one.enc4));
      nLSB=ioread8(&(q8Con->Q8reg->encoderData.one.enc4));
      nISB=ioread8(&(q8Con->Q8reg->encoderData.one.enc4));
      nMSB=ioread8(&(q8Con->Q8reg->encoderData.one.enc4));
       q8Str.dwNvalue=(nMSB << 16) | (nISB << 8) | nLSB;
       if(rtdm_safe_copy_to_user(user_info,buf,&q8Str,sizeof(struct_Q8_Config)))
            return -EFAULT;
   else 
     return 0;
}
///========================== FUNCTION HEADER =============================================================
/// Name        : Q8_ENC5_READ
/// Input       : cardNum  - PCI memory region that is mapped to Q8 card memory  
///               user_info- RTDM user information
///               buf      - USER memory region 
/// Output      : None
/// Return      : an integer value(not used)
/// Description : This function is used to read the encoder counter value  from the specified channel
///               
///========================================================================================================
int Q8_ENC5_READ(int cardNum,rtdm_user_info_t* user_info,void* buf){
       struct_Q8_Config q8Str;
   int8_t  nMSB;
   uint8_t nISB;
   uint8_t nLSB;
      iowrite8(ENC_ONE_CHANNEL | ENC_RLD_REGISTER | ENC_RLD_GET_CNTR | ENC_RLD_RESET_BP,
                 &(q8Con->Q8reg->encoderControl.one.enc5));
      nLSB=ioread8(&(q8Con->Q8reg->encoderData.one.enc5));
      nISB=ioread8(&(q8Con->Q8reg->encoderData.one.enc5));
      nMSB=ioread8(&(q8Con->Q8reg->encoderData.one.enc5));
       q8Str.dwNvalue=(nMSB << 16) | (nISB << 8) | nLSB;
       if(rtdm_safe_copy_to_user(user_info,buf,&q8Str,sizeof(struct_Q8_Config)))
       return -EFAULT;
   else 
     return 0;
}
///=============================================FUNCTION HEADER ========================================================
/// Name        : Q8_ENC6_READ
/// Input       : cardNum  - PCI memory region that is mapped to Q8 card memory  
///               user_info- RTDM user information
///               buf      - USER memory region 
/// Output      : None
/// Return      : an integer value(not used)
/// Description : This function is used to read the encoder counter value  from the specified channel
///               
///=====================================================================================================================
int Q8_ENC6_READ(int cardNum,rtdm_user_info_t* user_info,void* buf){
       struct_Q8_Config q8Str;
   int8_t  nMSB;
   uint8_t nISB;
   uint8_t nLSB;
      iowrite8(ENC_ONE_CHANNEL | ENC_RLD_REGISTER | ENC_RLD_GET_CNTR | ENC_RLD_RESET_BP,
                &(q8Con->Q8reg->encoderControl.one.enc6));
      nLSB=ioread8(&(q8Con->Q8reg->encoderData.one.enc6));
      nISB=ioread8(&(q8Con->Q8reg->encoderData.one.enc6));
      nMSB=ioread8(&(q8Con->Q8reg->encoderData.one.enc6));
       q8Str.dwNvalue=(nMSB << 16) | (nISB << 8) | nLSB;
        if(rtdm_safe_copy_to_user(user_info,buf,&q8Str,sizeof(struct_Q8_Config)))
   return -EFAULT;
   else 
     return 0;
}
///============================================ FUNCTION HEADER =================================================
/// Name        : Q8_ENC7_READ
/// Input       : cardNum  - PCI memory region that is mapped to Q8 card memory  
///               user_info- RTDM user information
///               buf      - USER memory region 
/// Output      : None
/// Return      : an integer value(not used)
/// Description : This function is used to read the encoder counter value  from the specified channel
///               
///===============================================================================================================
int Q8_ENC7_READ(int cardNum,rtdm_user_info_t* user_info,void* buf){
       struct_Q8_Config q8Str;
   int8_t  nMSB;
   uint8_t nISB;
   uint8_t nLSB;
      iowrite8(ENC_ONE_CHANNEL | ENC_RLD_REGISTER | ENC_RLD_GET_CNTR | ENC_RLD_RESET_BP,
                &(q8Con->Q8reg->encoderControl.one.enc7));
   nLSB=ioread8(&(q8Con->Q8reg->encoderData.one.enc7));
      nISB=ioread8(&(q8Con->Q8reg->encoderData.one.enc7));
      nMSB=ioread8(&(q8Con->Q8reg->encoderData.one.enc7));
      q8Str.dwNvalue=(nMSB << 16) | (nISB << 8) | nLSB;
        if(rtdm_safe_copy_to_user(user_info,buf,&q8Str,sizeof(struct_Q8_Config)))
            return -EFAULT;
   else 
     return 0;
}
///============================================ FUNCTION HEADER =================================================
/// Name        : Q8_ENCX_RESET
/// Input       : cardNum  - PCI memory region that is mapped to Q8 card memory  /*NOT
///               user_info- RTDM user information                                     USED
///               buf      - USER memory region                                             */
/// Output      : None
/// Return      : NOne
/// Description : This function is used to reset the encoder counter  belonging to the specified channel(X)
///               
///===============================================================================================================
int Q8_ENC0_RESET(int cardNum,rtdm_user_info_t* user_info,void* buf){
   iowrite32(ENC_RLD_RESET_CNTR,&(q8Con->Q8reg->encoderControl.one.enc0));
        return 0;
}
int Q8_ENC1_RESET(int cardNum,rtdm_user_info_t* user_info,void* buf){
   iowrite32(ENC_RLD_RESET_CNTR,&(q8Con->Q8reg->encoderControl.one.enc1));
    return 0;
}
int Q8_ENC2_RESET(int cardNum,rtdm_user_info_t* user_info,void* buf){
   iowrite32(ENC_RLD_RESET_CNTR,&(q8Con->Q8reg->encoderControl.one.enc2));
        return 0;
}
int Q8_ENC3_RESET(int cardNum,rtdm_user_info_t* user_info,void* buf){
   iowrite32(ENC_RLD_RESET_CNTR,&(q8Con->Q8reg->encoderControl.one.enc3));
        return 0;
}
int Q8_ENC4_RESET(int cardNum,rtdm_user_info_t* user_info,void* buf){
   iowrite32(ENC_RLD_RESET_CNTR,&(q8Con->Q8reg->encoderControl.one.enc4));
        return 0;
}
int Q8_ENC5_RESET(int cardNum,rtdm_user_info_t* user_info,void* buf){
   iowrite32(ENC_RLD_RESET_CNTR,&(q8Con->Q8reg->encoderControl.one.enc5));
   return 0;
}
int Q8_ENC6_RESET(int cardNum,rtdm_user_info_t* user_info,void* buf){
   iowrite32(ENC_RLD_RESET_CNTR,&(q8Con->Q8reg->encoderControl.one.enc6));
        return 0;
}
int Q8_ENC7_RESET(int cardNum,rtdm_user_info_t* user_info,void* buf){
        iowrite32(ENC_RLD_RESET_CNTR,&(q8Con->Q8reg->encoderControl.one.enc7));
        return 0;
}
///========================== FUNCTION HEADER =============================================================
/// Name        : Q8_Encoder_Config
/// Input       : cardNum  - PCI memory region that is mapped to Q8 card memory  
///               user_info- RTDM user information
///               buf      - USER memory region 
/// Output      : None
/// Return      : an integer value(not used)
/// Description : This function is used to configure the specified encoder channel
///               
///========================================================================================================
int Q8_Encoder_Config(int cardNum,rtdm_user_info_t* user_info,void* buf){
   struct_Q8_Config q8Str;
   if(rtdm_safe_copy_from_user(user_info, &q8Str,buf, sizeof(struct_Q8_Config)))
   return -EFAULT;
   (*encCountMode[q8Str.iChannelNum][q8Str.ubEcountMode])(cardNum); 
   (*encquadMode[q8Str.iChannelNum][q8Str.ubEquadratureMode])(cardNum);
   (*bcdorbinary[q8Str.iChannelNum][q8Str.ubEbcdMode])(cardNum);
   (*indexendisable[q8Str.iChannelNum][q8Str.ubIndexEnable])(cardNum);
   /*(**indexpolarity[q8Str.iChannelNum][q8Str.ubIndexPolarity])(0);*/
   return 0;
}
///========================== FUNCTION HEADER =============================================================
/// Name        : Q8_DAC_Config
/// Input       : cardNum  - PCI memory region that is mapped to Q8 card memory  
///               user_info- RTDM user information
///               buf      - USER memory region 
/// Output      : None
/// Return      : an integer value(not used)
/// Description : This function is used to configure the specified analog ouput channel
///               
///========================================================================================================
int Q8_DAC_Config(int cardNum,rtdm_user_info_t* user_info,void* buf){
   struct_Q8_Config q8Str;
   if(rtdm_safe_copy_from_user(user_info, &q8Str,buf, sizeof(struct_Q8_Config))){
   return -EFAULT;
   }
    (*dacConfigs[q8Str.iChannelNum][q8Str.ubDacMode])(q8Str.iCardNum);
   return 0;
}   
///========================== FUNCTION HEADER ================================================================
/// Name        : Q8_TIMER_CR
/// Input       : cardNum  - PCI memory region that is mapped to Q8 card memory  
///               user_info- RTDM user information
///               buf      - USER memory region 
/// Output      : None
/// Return      : an integer value(not used)
/// Description : This function is used to set preload value(period) of 32 bit timer.Counter is used as timer.
///               
///=============================================================================================================
int Q8_TIMER_SET(int cardNum,rtdm_user_info_t* user_info,void* buf){
        rtdm_printk("q8timer set called!");
        struct_Q8_Config q8Str;
        if(rtdm_safe_copy_from_user(user_info, &q8Str,buf, sizeof(struct_Q8_Config))){
   return -EFAULT;
   }
   /*disables interrupts from the counter*/
        iowrite32((0xffffffff),&(q8Con->Q8reg->interruptStatus));
   udwIntEnable=ioread32(&(q8Con->Q8reg->interruptEnable));//INT_CNTROUT    0x00100000
   iowrite32((udwIntEnable & INT_CNTROUT),&(q8Con->Q8reg->interruptEnable));
        iowrite32(q8Str.udwPeriod,&(q8Con->Q8reg->counter.sq.preload));      
        return 0;            
}
int Q8_TIMER_START(int cardNum,rtdm_user_info_t* user_info,void* buf){
   rtdm_printk("q8timer start called!");   
   /*enable the counter*/
   iowrite32(CCTRL_CNTREN,&(q8Con->Q8reg->counterControl));
        /*force the counter to load immediately*/
   iowrite32(CCTRL_CNTREN | CCTRL_CNTRLD | CCTRL_CNTRVAL ,&(q8Con->Q8reg->counterControl));
        /*enable interrupts from the counter*/
        udwIntEnable|=INT_CNTROUT;
        iowrite32((0xffffffff),&(q8Con->Q8reg->interruptStatus));
        iowrite32((udwIntEnable),&(q8Con->Q8reg->interruptEnable));
        return 0;            
}
int   Q8_TIMERINT_EN(int cardNum,rtdm_user_info_t* user_info,void* buf){
   rtdm_printk("q8timer enable called!");
   udwIntEnable|=INT_CNTROUT;
   iowrite32((0xffffffff),&(q8Con->Q8reg->interruptStatus));
        iowrite32((udwIntEnable),&(q8Con->Q8reg->interruptEnable));
        return 0; 
}
int Q8_TIMER_STOP(int cardNum,rtdm_user_info_t* user_info,void* buf){
   rtdm_printk("q8timer stop called!");
        countercontrol&=0xFFFFFFFE;
        iowrite32(countercontrol ,&(q8Con->Q8reg->counterControl));
        return 0;            
}
int  Q8_GET_IRQ(int cardNum,rtdm_user_info_t* user_info,void* buf){
        //rtdm_printk("irq get called!!!!!!!!\n");
   struct_Q8_Config q8Str;
        q8Str.irq=q8Con->irq_line;
        if(rtdm_safe_copy_to_user(user_info,buf,&q8Str,sizeof(struct_Q8_Config)))
   return -EFAULT;
   else 
        return 0;
}
/* UTILITY FUNCTION POINTERS*/
static int (*const functions[45])(int,rtdm_user_info_t*,void*)={                 
                     Q8_DAC0_WRITE,
                                                  Q8_DAC1_WRITE,
                          Q8_DAC2_WRITE,
                                                  Q8_DAC3_WRITE,
                                                  Q8_DAC4_WRITE,
                                                  Q8_DAC5_WRITE,
                                                  Q8_DAC6_WRITE,
                                                  Q8_DAC7_WRITE,
                                                  Q8_ADC0READ,
                                        Q8_ADC1READ,
                    Q8_ADC2READ,                  
                    Q8_ADC3READ,
                                                  Q8_ADC4READ,   
                    Q8_ADC5READ,
                    Q8_ADC6READ,   
                                                  Q8_ADC7READ,
                                                  Q8_ENC0_READ,
                                                  Q8_ENC1_READ,
                                                  Q8_ENC2_READ,
                    Q8_ENC3_READ,
                                                  Q8_ENC4_READ,
                                                  Q8_ENC5_READ,
                                                  Q8_ENC6_READ,
                                                  Q8_ENC7_READ,
                                                  Q8_Digital_Output,
                                                  Q8_Digital_Input,
                                                  Q8_Counter_Output,
                                                  Q8_PWM_Output,
                                                  Q8_Watchdog_Timer, 
                                                  Q8_Encoder_Config,
                                Q8_DAC_Config,
                                                  Q8_ENC0_RESET,
                                                  Q8_ENC1_RESET,
                                                  Q8_ENC2_RESET,
                    Q8_ENC3_RESET,
                                                  Q8_ENC4_RESET,
                                                  Q8_ENC5_RESET,
                                                  Q8_ENC6_RESET,
                                                  Q8_ENC7_RESET,
                    Q8_TIMER_SET,
                                                  Q8_TIMER_START,
                                                  Q8_TIMER_STOP,
                                                  Q8_GET_IRQ,
                                                  Q8_TIMERINT_EN,                            
};
///==============================================FUNCTION HEADER=======================================================
/// Name        : Q8_rt_rw
/// Input       : context  - RTDM API    
///               user_info- RTDM user information
///               buf      - USER memory region 
///               nbyte    - size of memory region to which is pointed 
/// Output      : None
/// Return      : an integer value(not used)
/// Description : This function is used to call all utility driver functions that is needed.This function is
///               the only function that is registered as a real driver function in RTDM strucrure.
///               All user functions call this function via RTDM API.
///               
///===========================================================================================================
int Q8_rt_rw(struct rtdm_dev_context *context ,rtdm_user_info_t* user_info,void* buf,size_t nbyte)
{
    struct_Q8_Config q8Str;
   if(rtdm_safe_copy_from_user(user_info, &q8Str,buf, sizeof(struct_Q8_Config))){
        return -EFAULT;}
        (*functions[q8Str.uiFuncIndex])(q8Str.iCardNum,user_info,buf);
   return 0;
}
///========================== FUNCTION HEADER =====================================================================
/// Name        : Q8_probe
/// Input       : dev           -   LINUX pci api
///               pci_device_id -   LINUX pci api
/// Output      : None
/// Return      : an integer value(not used)
/// Description : This function is called on boot time and initilaze the pci card.I took this function partly
///               from a weblink.You can find it in www.xenomai.org.It is called two times so it can only be used
///               for a single card.This means the rtdm driver works for a single card.It must be modified. 
///               
///================================================================================================================
static int Q8_probe(struct pci_dev *dev, const struct pci_device_id *id){/*__devinit */
   struct rtdm_device *rtdm_dev;
        int intr_err;
   int ret_val = 0;
   int i;
        uint8_t irq;
   //if-condition evaluates to true in the second loop
   if(first_loop){
       //first_loop =1;
     return ret_loop_val;
   }
   first_loop=1;
   //wake up the device
   ret_val = pci_enable_device(dev);
   if(ret_val!=0){
       printk( KERN_WARNING
         "xen_Q8_driver: function pci_enable_device failed\n");
     goto pci_enable_device_err;
   }
   rtdm_printk(KERN_DEBUG "device woke up!\n");
    //initialization of location and mem_size
   q8Con->location = pci_resource_start(dev,Q8_BAR);
   q8Con->mem_size = pci_resource_len(dev,Q8_BAR);
        intr_err=pci_read_config_byte(dev,PCI_INTERRUPT_LINE,&irq);
        if (!intr_err){
      rtdm_printk("interrupt line no:%d",irq);   
   }
        q8Con->irq_line=irq;
        rtdm_printk("Q8 irq line number is: %d\n ",q8Con->irq_line);
   //alloc mem for rtdm structure
   rtdm_dev = kmalloc(sizeof(struct rtdm_device), GFP_KERNEL);
   if(!rtdm_dev){
        rtdm_printk(KERN_WARNING "xen_Q8_driver: kmalloc failed\n");
        ret_val = -ENOMEM; //Insufficient storage space is available.
        //pci_disable_device(dev); 
        goto kmalloc_err;
   }
   //copy the structure to the new memory
   memcpy(rtdm_dev, &xen_Q8_driver, sizeof(struct rtdm_device));
   //create filename
   snprintf(rtdm_dev->device_name,
         RTDM_MAX_DEVNAME_LEN, "Q8%d", 0 /*i*/);
   rtdm_dev->device_id = 0; //i;
   //define two other members of the rtdm_device structure
   rtdm_dev->proc_name = rtdm_dev->device_name;
   //allocate memory region for CPCI card
   if(request_mem_region(q8Con->location,
         q8Con->mem_size, rtdm_dev->device_name)==NULL){
       rtdm_printk(KERN_WARNING
        "xen_Q8_driver: device memory allocation failed!\n");
        ret_val = -EBUSY;
        goto request_mem_region_err;
      }
   rtdm_printk( KERN_DEBUG "going to map memory to kernel space\n");
   //map IO mem to kernel space
   q8Con->base_address=ioremap(q8Con->location,q8Con->mem_size);
   q8Con->Q8reg=(struct tagQ8Registers * )(q8Con->base_address);
   if(!q8Con->base_address){
     rtdm_printk(KERN_WARNING
      "xen_Q8_driver: cannot remap memory region\n");
     ret_val = -ENODEV;
     goto ioremap_err;
}
   rtdm_printk(KERN_DEBUG "base address@length is %p @ %lx\n",
       q8Con->base_address, q8Con->mem_size);
   /*configuration of D/A outputs---------BIPOLAR 10V MODE*/
   /*AND all outputs will be "bipolar zero"*/ 
   iowrite32(0x0FF00FF0L,&(q8Con->Q8reg->analogMode.all));//change mode

   for(i=0;i<4;i++){
   iowrite32(0x08000800L,&(q8Con->Q8reg->analogOutput.pairs[i]));
   }
   iowrite32(0,&(q8Con->Q8reg->analogUpdate.all));
   iowrite32(0,&(q8Con->Q8reg->analogModeUpdate.all));
   /*DIGITAL I/O INIT */ 
   iowrite32(0xffffffff,&(q8Con->Q8reg->digitalDirection));//all output
   iowrite32(0x00000000,&(q8Con->Q8reg->digitalIO));//0
   /*ANALOG INPUT INIT.*/
   cntrl=ioread32(&(q8Con->Q8reg->control));
   cntrl=((cntrl & 0xFF0000FF) | CTRL_ADC03HS | 
   CTRL_ADC03SCK | CTRL_ADC47HS | CTRL_ADC47SCK  );
   iowrite32(cntrl,&(q8Con->Q8reg->control));
   /*initialize encoder*/
   static const uint32_T cmrInit  = ENC_BOTH_CHANNELS | ENC_CMR_REGISTER | ENC_CMR_BINARY | ENC_CMR_NORMAL | ENC_CMR_QUADRATURE_4X;
   static const uint32_T rldInit1 = ENC_BOTH_CHANNELS | ENC_RLD_REGISTER | ENC_RLD_RESET_BP | ENC_RLD_RESET_E;
   static const uint32_T rldInit2 = ENC_BOTH_CHANNELS | ENC_RLD_REGISTER | ENC_RLD_RESET_BP | ENC_RLD_RESET_FLAGS | ENC_RLD_SET_PSC;
   static const uint32_T rldInit3 = ENC_BOTH_CHANNELS | ENC_RLD_REGISTER | ENC_RLD_RESET_BP | ENC_RLD_RESET_CNTR;
   static const uint32_T iorInit  = ENC_BOTH_CHANNELS | ENC_IOR_REGISTER | ENC_IOR_ENABLE_AB | ENC_IOR_LCNTR_LATCH | ENC_IOR_INDEX_ERROR;
   static const uint32_T idrInit  = ENC_BOTH_CHANNELS | ENC_IDR_REGISTER | ENC_IDR_DISABLE_INDEX | ENC_IDR_POS_INDEX | ENC_IDR_LCNTR_INDEX;
   
   iowrite32( (cmrInit << 24) | (cmrInit << 16) | (cmrInit <<8) | (cmrInit),&(q8Con->Q8reg->encoderControl.four.enc0246))  ;
   iowrite32((rldInit1 << 24) | (rldInit1 << 16) | (rldInit1 << 8) | (rldInit1),&(q8Con->Q8reg->encoderControl.four.enc0246));            
            
   iowrite32(0,&(q8Con->Q8reg->encoderData.four.enc0246));
   iowrite32(0,&(q8Con->Q8reg->encoderData.four.enc1357));
   iowrite32(0,&(q8Con->Q8reg->encoderData.four.enc0246));
   iowrite32(0,&(q8Con->Q8reg->encoderData.four.enc1357));
   iowrite32(0,&(q8Con->Q8reg->encoderData.four.enc0246));
   iowrite32(0,&(q8Con->Q8reg->encoderData.four.enc1357));

   iowrite32( (rldInit2 << 24) | (rldInit2 << 16) | (rldInit2 << 8) | (rldInit2),&(q8Con->Q8reg->encoderControl.four.enc0246));
   iowrite32((rldInit3 << 24) | (rldInit3 << 16) | (rldInit3 << 8) | (rldInit3),&(q8Con->Q8reg->encoderControl.four.enc0246));         
   iowrite32((iorInit << 24) | (iorInit << 16) | (iorInit << 8) | (iorInit),&(q8Con->Q8reg->encoderControl.four.enc0246));
   iowrite32((idrInit << 24) | (idrInit << 16) | (idrInit << 8) | (idrInit),&(q8Con->Q8reg->encoderControl.four.enc0246));
   /*control register backup */
   cntrl=ioread32(&(q8Con->Q8reg->control));
   iowrite32(cntrl & 0xffffff00L,&(q8Con->Q8reg->control));
   /* COUNTER INITIALIZATION*/
   iowrite32(CCTRL_CNTRWSET | CCTRL_WDOGWSET,&(q8Con->Q8reg->counterControl));
   iowrite32(0,&(q8Con->Q8reg->counter.pwm.preloadLow));
   iowrite32(0,&(q8Con->Q8reg->counter.pwm.preloadHigh));
   iowrite32(0,&(q8Con->Q8reg->counter.pwm.preloadLow));
   iowrite32(0,&(q8Con->Q8reg->watchdog.pwm.preloadHigh));
   iowrite32(0,&(q8Con->Q8reg->counterControl));
   iowrite32(0,&(q8Con->Q8reg->counter.pwm.preloadLow));
   iowrite32(0,&(q8Con->Q8reg->counter.pwm.preloadHigh));
   iowrite32(0,&(q8Con->Q8reg->counter.pwm.preloadLow));
   iowrite32(0,&(q8Con->Q8reg->watchdog.pwm.preloadHigh));
   
   /*INTERRUPTS DISABLED*/
   iowrite32(0,&(q8Con->Q8reg->interruptEnable));
          
   countercontrol=ioread32(&(q8Con->Q8reg->counterControl));
   ret_val = rtdm_dev_register(rtdm_dev);
   if(ret_val < 0){
     goto dev_register_err;
   }
     q8Con->xen_device = rtdm_dev;
     return ret_val;
     //clean up code in case of errors
     dev_register_err:
         iounmap(q8Con->base_address);
         iounmap(q8Con->Q8reg);
     ioremap_err:
         release_mem_region(q8Con->location,
                         q8Con->mem_size);
     request_mem_region_err:
         kfree(rtdm_dev);
     kmalloc_err:
     pci_enable_device_err:
     ret_loop_val = ret_val;
     return ret_val;
}

///========================== FUNCTION HEADER =========================================================================
/// Name        : Q8_remove
/// Input       : pci_dev -   LINUX pci api
/// Output      : None
/// Return      : an integer value(not used)
/// Description : This function is called when module is removed or on reboot time and prepares  the pci card to reset.
///               I took this function partly  from a weblink.You can find it in www.xenomai.org.It is called
///              two times so it can only be used for a single card.This means the rtdm driver works for a single                 
///               card.It must be modified.                    
///=====================================================================================================================

static void  Q8_remove(struct pci_dev *dev)/*__devexit*/
{
 
  if(!first_loop){
    //first_loop=0;
    return;
  }
  first_loop=0;
/*configuration of D/A outputs---------BIPOLAR 10V MODE*/
/*AND all outputs will be "bipolar zero"*/ 
   iowrite32(0x08000800,q8Con->base_address+0x40);//"0 V",registerA(channel 04)
   iowrite32(0x08000800,q8Con->base_address+0x44);//  "  ,registerB(channel 15) 
   iowrite32(0x08000800,q8Con->base_address+0x48);//  "  ,registerC(channel 26)
   iowrite32(0x08000800,q8Con->base_address+0x4C);//  "  ,registerD(channel 37)
/*UPDATE D/A OUTPUTS*/
   iowrite32(0x00000000,q8Con->base_address+0x50);//update channel values;
/*DISABLE COUNTER*/
   iowrite32(countercontrol & 0x00000000,&(q8Con->Q8reg->counterControl));//update channel values;
/*DIGITAL I/0*/
   iowrite32(0xffffffff,&(q8Con->Q8reg->digitalDirection));//all output
   iowrite32(0x00000000,&(q8Con->Q8reg->digitalIO));//0
/*ENCODER RESET*/
   iowrite32(ENC_RLD_RESET_CNTR,&(q8Con->Q8reg->encoderControl.one.enc0));
   iowrite32(ENC_RLD_RESET_CNTR,&(q8Con->Q8reg->encoderControl.one.enc1));
   iowrite32(ENC_RLD_RESET_CNTR,&(q8Con->Q8reg->encoderControl.one.enc2));
   iowrite32(ENC_RLD_RESET_CNTR,&(q8Con->Q8reg->encoderControl.one.enc3));
   iowrite32(ENC_RLD_RESET_CNTR,&(q8Con->Q8reg->encoderControl.one.enc4));
   iowrite32(ENC_RLD_RESET_CNTR,&(q8Con->Q8reg->encoderControl.one.enc5));      
   iowrite32(ENC_RLD_RESET_CNTR,&(q8Con->Q8reg->encoderControl.one.enc6));
   iowrite32(ENC_RLD_RESET_CNTR,&(q8Con->Q8reg->encoderControl.one.enc7));
        rtdm_dev_unregister(q8Con->xen_device, 1000);
 
  //release virtual memory
     iounmap(q8Con->base_address);
     iounmap(q8Con->Q8reg);//cok onemli
   //release memory region
     release_mem_region(q8Con->location,q8Con->mem_size);
 
  //free allocated memory
     kfree(q8Con->xen_device);
}
/**
 * Init module function
 */
static int xen_Q8_driver_init_module(void)
{
     static int ret_val;

     ret_val = pci_register_driver(&quanser_Q8_driver);
     return ret_val;
}
/**
 * Exit module function
 */

static void xen_Q8_driver_exit_module(void)
{

     pci_unregister_driver(&quanser_Q8_driver);
}
   module_init(xen_Q8_driver_init_module);
   module_exit(xen_Q8_driver_exit_module);





