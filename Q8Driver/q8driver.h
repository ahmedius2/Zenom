#ifndef _QUANSER_Q8_DRIVER_H_
#define _QUANSER_Q8_DRIVER_H_

#define DRV_NAME        "q8_driver"
#define Q8_VENDOR_ID_QUANSER  0x11E3
#define Q8_SUBVENDOR_ID_QUANSER 0x5155
#define Q8_DEVICE_ID     0x0010
#define Q8_SUBDEVICE_ID   0x0200
#define Q8_BAR            0x00
/**
 * IOCTL stuff
 */
static int  Q8_probe(struct pci_dev *dev,
                                      const struct pci_device_id *id);/*__devinit*/
static void  Q8_remove(struct pci_dev *dev); /* __devexit */

uint32_t cntrl=0;
int i;
struct Q8_Config{
	int iChannelNum;
 	int iCardNum;
	int16_t wValueSigned;
	uint16_t uwValueUnsigned;//Analog output value
	unsigned int uiFuncIndex;
	uint8_t ubDacMode;
	uint8_t  ubEcountMode;/*encoder*/
	uint8_t ubEbcdMode;
	uint8_t ubEquadratureMode;
	uint8_t ubIndexEnable;
	uint8_t ubIndexPolarity;
	int32_t dwNvalue;//encoder counter value
	uint32_t udwDataDirection;/*digital I/0*/
	uint32_t udwDataRegister;
	int iClockSource;/*COUNTER*/
	uint32_t udwPeriod;
	uint32_t udwLow;
	uint32_t udwHigh;
	int iCntrlEn;
        uint8_t irq;
        int onlyDigitalData;
};
typedef struct Q8_Config struct_Q8_Config;
typedef uint32_t uint32_T;
typedef int32_t  int32_T;
typedef int16_t  int16_T;
typedef uint8_t  uint8_T;
typedef uint16_t  uint16_T;
typedef uint64_t  uint64_T;

struct tagQ8Registers
{
    uint32_T interruptEnable;
    int32_T  interruptStatus;
    uint32_T control;
    uint32_T status;

    union
    {
        struct
        {
            uint32_T preload;
            uint32_T value;
        } sq;

        struct
        {
            uint32_T preloadLow;
            uint32_T preloadHigh;
        } pwm;
    } counter;

    union
    {
        struct
        {
            uint32_T preload;
            uint32_T value;
        } sq;

        struct
        {
            uint32_T preloadLow;
            uint32_T preloadHigh;
        } pwm;
    } watchdog;

    uint32_T counterControl;
    uint32_T digitalIO;
    uint32_T digitalDirection;

    union
    {
        struct {
            int16_T adc03;
            int16_T adc47;
        } one;

        int32_T two;      
        int32_T select;  
    } analogInput;

    union
    {
        struct {
            uint8_T enc0;
            uint8_T enc2;
            uint8_T enc4;
            uint8_T enc6;

            uint8_T enc1;
            uint8_T enc3;
            uint8_T enc5;
            uint8_T enc7;
        } one;

        uint8_T encs[8];

        struct {
            uint16_T enc02;
            uint16_T enc46;

            uint16_T enc13;
            uint16_T enc57;
        } two;

        struct {
            uint32_T enc0246;   
            uint32_T enc1357;   
        } four;

        uint64_T all;
    } encoderData;

    union
    {
        struct {
            uint8_T enc0;
            uint8_T enc2;
            uint8_T enc4;
            uint8_T enc6;

            uint8_T enc1;
            uint8_T enc3;
            uint8_T enc5;
            uint8_T enc7;
        } one;

        uint8_T encs[8];

        struct {
            uint16_T enc02;
            uint16_T enc46;

            uint16_T enc13;
            uint16_T enc57;
        } two;

        struct {
            uint32_T enc0246;   
            uint32_T enc1357;  
        } four;

        uint64_T all;
    } encoderControl;

    union
    {
        struct {
            uint16_T dac0;
            uint16_T dac4;

            uint16_T dac1;
            uint16_T dac5;

            uint16_T dac2;
            uint16_T dac6;

            uint16_T dac3;
            uint16_T dac7;
        } one;

        uint16_T dacs[8];

        struct {
            uint32_T dac04;
            uint32_T dac15;
            uint32_T dac26;
            uint32_T dac37;
        } two;

        uint32_T pairs[4];

        struct
        {
            uint64_T dac0415;
            uint64_T dac2637;
        } four;
    } analogOutput;

    union
    {
        struct {
            uint16_T dac03;
            uint16_T dac47;
        } four;

        uint32_T all;
    } analogUpdate;

    uint32_T reserved2[6];
    
    union
    {
        struct {
            uint16_T dac03;
            uint16_T dac47;
        } four;

        uint32_T all;
    } analogMode;

    union
    {
        struct {
            uint16_T dac03;
            uint16_T dac47;
        } four;

        uint32_T all;
    } analogModeUpdate;

    uint32_T reserved3[227];

} ;
 
  
#define INT_PEND       0x80000000   /* Card is asserting interrupt line (enabled interrupt source detected) */
#define INT_EXTINT     0x00800000   /* Edge detected on EXT_INT line (external interrupt signalled) */
#define INT_FUSE       0x00400000   /* Rising edge detected on FUSE input (fuse blown) */
#define INT_WATCHDOG   0x00200000   /* Watchdog counter expired */
#define INT_CNTROUT    0x00100000   /* General purpose counter expired */
#define INT_ADC47RDY   0x00080000   /* A/D converter on channels 4-7 is finished conversions (and ready to do more) */
#define INT_ADC03RDY   0x00040000   /* A/D converter on channels 0-3 is finished conversions (and ready to do more) */
#define INT_ADC47EOC   0x00020000   /* A/D converter on channels 4-7 has completed a conversion */
#define INT_ADC03EOC   0x00010000   /* A/D converter on channels 0-3 has completed a conversion */
#define INT_ENC7FLG2   0x00008000   /* Rising edge detected on encoder channel 7 flag 2  */
#define INT_ENC7FLG1   0x00004000   /* Rising edge detected on encoder channel 7 flag 1 */
#define INT_ENC6FLG2   0x00002000   /* Rising edge detected on encoder channel 6 flag 2 */
#define INT_ENC6FLG1   0x00001000   /* Rising edge detected on encoder channel 6 flag 1 */
#define INT_ENC5FLG2   0x00000800   /* Rising edge detected on encoder channel 5 flag 2 */
#define INT_ENC5FLG1   0x00000400   /* Rising edge detected on encoder channel 5 flag 1 */
#define INT_ENC4FLG2   0x00000200   /* Rising edge detected on encoder channel 4 flag 2 */
#define INT_ENC4FLG1   0x00000100   /* Rising edge detected on encoder channel 4 flag 1 */
#define INT_ENC3FLG2   0x00000080   /* Rising edge detected on encoder channel 3 flag 2 */
#define INT_ENC3FLG1   0x00000040   /* Rising edge detected on encoder channel 3 flag 1 */
#define INT_ENC2FLG2   0x00000020   /* Rising edge detected on encoder channel 2 flag 2 */
#define INT_ENC2FLG1   0x00000010   /* Rising edge detected on encoder channel 2 flag 1 */
#define INT_ENC1FLG2   0x00000008   /* Rising edge detected on encoder channel 1 flag 2 */
#define INT_ENC1FLG1   0x00000004   /* Rising edge detected on encoder channel 1 flag 1 */
#define INT_ENC0FLG2   0x00000002   /* Rising edge detected on encoder channel 0 flag 2 */
#define INT_ENC0FLG1   0x00000001   /* Rising edge detected on encoder channel 0 flag 1 */

#define CTRL_ADC47CV    0x00800000  /* 0 = no conversions on ADC47, 1 = start conversions on ADC47 */
#define CTRL_ADCSTBY    0x00400000  /* 0 = full power mode, 1 = A/D standby mode */
#define CTRL_ADC47CT    0x00200000  /* 0 = manual conversions on ADC47, 1 = use auto conversions */
#define CTRL_ADC47HS    0x00100000  /* 0 = Control Register selects channels, 1 = A/D Register selects channels */
#define CTRL_ADCSL7     0x00080000  /* 0 = do not include channel 7, 1 = include channel 7 in conversions */
#define CTRL_ADCSL6     0x00040000  /* 0 = do not include channel 6, 1 = include channel 6 in conversions */
#define CTRL_ADCSL5     0x00020000  /* 0 = do not include channel 5, 1 = include channel 5 in conversions */
#define CTRL_ADCSL4     0x00010000  /* 0 = do not include channel 4, 1 = include channel 4 in conversions */
#define CTRL_ADC03CV    0x00008000  /* 0 = no conversions on ADC03, 1 = start conversions on ADC03 */
                     /* 0x00004000  // reserved. Set to zero. */
#define CTRL_ADC03CT    0x00002000  /* 0 = manual conversions on ADC03, 1 = use auto conversions */
#define CTRL_ADC03HS    0x00001000  /* 0 = Control Register selects channels, 1 = A/D Register selects channels */
#define CTRL_ADCSL3     0x00000800  /* 0 = do not include channel 3, 1 = include channel 3 in conversions */
#define CTRL_ADCSL2     0x00000400  /* 0 = do not include channel 2, 1 = include channel 2 in conversions */
#define CTRL_ADCSL1     0x00000200  /* 0 = do not include channel 1, 1 = include channel 1 in conversions */
#define CTRL_ADCSL0     0x00000100  /* 0 = do not include channel 0, 1 = include channel 0 in conversions */

#define CCTRL_WDOGLD    0x02000000  /* 0 = no load operation, 1 = load watchdog counter from active preload and WDOGVAL */
#define CCTRL_WDOGVAL   0x01000000  /* value of watchdog counter output (ignored if WDOGLD = 0) */
#define CCTRL_WDOGACT   0x00800000  /* 0 = deactive watchdog features of WATCHDOG counter, 1 = active watchdog features */
#define CCTRL_WDOGSEL   0x00400000  /* 0 = WATCHDOG output reflects watchdog interrupt state (active low), 1 = output is output of WATCHDOG counter */
#define CCTRL_WDOGOUTEN 0x00200000  /* 0 = disable WATCHDOG output (output always high), 1 = enable WATCHDOG output. Value determined by WDOGSEL */
#define CCTRL_WDOGPRSEL 0x00100000  /* 0 = use Watchdog Preload Low Register, 1 = use Watchdog Preload High Register. Ignored if WDOGMODE = 1. */
#define CCTRL_WDOGWSET  0x00080000  /* 0 = use watchdog register set #0 for writes to preload registers, 1 = use register set #1 */
#define CCTRL_WDOGRSET  0x00040000  /* 0 = use watchdog register set #0 for active set and reads, 1 = use register set #1 */
#define CCTRL_WDOGMODE  0x00020000  /* 0 = square wave mode (WDOGPRSEL selects preload register), 1 = PWM mode (both preload low and high registers used) */
#define CCTRL_WDOGEN    0x00010000  /* 0 = disable counting of watchdog counter, 1 = enable watchdog counter */

#define CCTRL_CNTRLD    0x00000200  /* 0 = no load operation, 1 = load counter from active preload and CNTRVAL */
#define CCTRL_CNTRVAL   0x00000100  /* value of counter output (ignored if CNTRLD = 0) */
#define CCTRL_CNTRENPOL 0x00000040  /* 0 = CNTREN active high (CNTRENCV=0) or falling edge (CNTRENCV=1), 1 = opposite */
#define CCTRL_CNTROUTEN 0x00000020  /* 0 = disable CNTR_OUT output (output always high), 1 = enable CNTR_OUT output. Value is output of COUNTER */
#define CCTRL_CNTRPRSEL 0x00000010  /* 0 = use Counter Preload Low Register, 1 = use Counter Preload High Register. Ignored if CNTRMODE = 1 */
#define CCTRL_CNTRWSET  0x00000008  /* 0 = use counter register set #0 for writes to preload registers, 1 = use register set #1 */
#define CCTRL_CNTRRSET  0x00000004  /* 0 = use counter register set #0 for active set and reads, 1 = use register set #1 */
#define CCTRL_CNTRMODE  0x00000002  /* 0 = square wave mode (CNTRPRSEL selects preload register), 1 = PWM mode (both preload low and high registers used) */
#define CCTRL_CNTREN    0x00000001  /* 0 = disable counting of counter, 1 = enable counter */

#define CTRL_ADC47SCK   CTRL_ADCSL5 /* 0 = use internal clock for ADC47, 1 = use common clock */
#define CTRL_ADC03SCK   CTRL_ADCSL1 /* 0 = use internal clock for ADC03, 1 = use common clock */
#define STAT_CNTREN     0x01000000
#define STAT_EXTINT     0x00800000
#define STAT_FUSE       0x00400000
#define STAT_ADC47FST   0x00200000
#define STAT_ADC03FST   0x00100000
#define STAT_ADC47RDY   0x00080000
#define STAT_ADC03RDY   0x00040000
#define STAT_ADC47EOC   0x00020000
#define STAT_ADC03EOC   0x00010000
#define STAT_ENC7FLG2   0x00008000
#define STAT_ENC7FLG1   0x00004000
#define STAT_ENC6FLG2   0x00002000
#define STAT_ENC6FLG1   0x00001000
#define STAT_ENC5FLG2   0x00000800
#define STAT_ENC5FLG1   0x00000400
#define STAT_ENC4FLG2   0x00000200
#define STAT_ENC4FLG1   0x00000100
#define STAT_ENC3FLG2   0x00000080
#define STAT_ENC3FLG1   0x00000040
#define STAT_ENC2FLG2   0x00000020
#define STAT_ENC2FLG1   0x00000010
#define STAT_ENC1FLG2   0x00000008
#define STAT_ENC1FLG1   0x00000004
#define STAT_ENC0FLG2   0x00000002
#define STAT_ENC0FLG1   0x00000001

/* Encoder Control Byte bit definitions */
#define ENC_ONE_CHANNEL         0x00    /* operate on only one channel (according to which byte accessed) */
#define ENC_BOTH_CHANNELS       0x80    /* operate on both the even and odd channel */

#define ENC_RLD_REGISTER        0x00    /* select Reset and Load Signal Decoders Register (RLD) */

#define ENC_RLD_RESET_BP        0x01    /* reset byte pointer (BP) */

#define ENC_RLD_RESET_CNTR      0x02    /* reset count value (CNTR) to zero  */
#define ENC_RLD_RESET_FLAGS     0x04    /* reset flags (borrow (BT), carry (CT), compare (CPT) and sign (S) flags) */
#define ENC_RLD_RESET_E         0x06    /* reset error flag (E) */

#define ENC_RLD_SET_CNTR        0x08    /* transfer preload register (PR) to counter (CNTR) */
#define ENC_RLD_GET_CNTR        0x10    /* transfer counter (CNTR) to output latch (OL) */
#define ENC_RLD_SET_PSC         0x18    /* transfer preload register LSB (PR0) to filter prescaler (PSC) */

#define ENC_CMR_REGISTER        0x20    /* select Counter Mode Register (CMR) */

#define ENC_CMR_BINARY          0x00    /* binary count mode */
#define ENC_CMR_BCD             0x01    /* BCD count mode */

#define ENC_CMR_NORMAL          0x00    /* normal count (24-bit value which wraps on overflow or underflow) */
#define ENC_CMR_RANGE           0x02    /* range limit (counter freezes at zero (CNTR=0) or preload value (CNTR=PR), count resumes when direction reversed) */
#define ENC_CMR_NONRECYCLE      0x04    /* non-recycle count (counter disabled on underflow or overflow, re-enabled by reset or load operation on CNTR) */
#define ENC_CMR_MODULO          0x06    /* modulo-N (counter reset to zero when CNTR=PR, set to PR when CNTR=0). */

#define ENC_CMR_NONQUADRATURE   0x00    /* non-quadrature mode (digital count and direction inputs instead of encoder A and B signals) */
#define ENC_CMR_QUADRATURE_1X   0x08    /* quadrature 1X mode */
#define ENC_CMR_QUADRATURE_2X   0x10    /* quadrature 1X mode */
#define ENC_CMR_QUADRATURE_4X   0x18    /* quadrature 1X mode */

#define ENC_IOR_REGISTER        0x40    /* select Input/Output Control Register (IOR) */

#define ENC_IOR_DISABLE_AB      0x00    /* disable A and B inputs */
#define ENC_IOR_ENABLE_AB       0x01    /* enable A and B inputs */

#define ENC_IOR_LCNTR_LOAD      0x00    /* LCNTR/LOL pin is Load CNTR */
#define ENC_IOR_LCNTR_LATCH     0x02    /* LCNTR/LOL pin is Latch CNTR in OL */

#define ENC_IOR_RCNTR_RESET     0x00    /* RCNTR/ABG pin is Reset CNTR */
#define ENC_IOR_RCNTR_GATE      0x04    /* RCNTR/ABG pin is A and B Enable gate */

#define ENC_IOR_CARRY_BORROW    0x00    /* FLG1 is CARRY, FLG2 is BORROW */
#define ENC_IOR_COMPARE_BORROW  0x08    /* FLG1 is COMPARE, FLG2 is BORROW */
#define ENC_IOR_CARRY_UPDOWN    0x10    /* FLG1 is CARRY/BORROW, FLG2 is UP/DOWN (FLAG bit 5) */
#define ENC_IOR_INDEX_ERROR     0x18    /* FLG1 is IDX (FLAG bit 6), FLG2 is E (FLAG bit 4) */

#define ENC_IDR_REGISTER        0x60    /* Index Control Register (IDR) */

#define ENC_IDR_DISABLE_INDEX   0xFE    /* bunun değeri orlama işlemin de 0x00 ben & işlemi yaptım.  */
#define ENC_IDR_ENABLE_INDEX    0x01    /* Enable index */

#define ENC_IDR_NEG_INDEX       0x00    /* Negative index polarity */
#define ENC_IDR_POS_INDEX       0x02    /* Positive index polarity */

#define ENC_IDR_LCNTR_INDEX     0x00    /* LCNTR/LOL pin is indexed */
#define ENC_IDR_RCNTR_INDEX     0x04    /* RCNTR/ABG pin is indexed (*** do not use with Q8 card ***) */
uint16_t value[8];
uint16_t analogModecurrent;
uint8_t encoderControlcurrent;

#define DAC04_MASK 0x0770
#define DAC0_UNIPOLAR_10V 0x0000
#define DAC0_BIPOLAR_5V   0x0080
#define DAC0_BIPOLAR_10V  0x0880

#define DAC15_MASK 0x0BB0
#define DAC1_UNIPOLAR_10V 0x0000
#define DAC1_BIPOLAR_5V   0x0040
#define DAC1_BIPOLAR_10V  0x0440

#define DAC26_MASK 0x0DD0
#define DAC2_UNIPOLAR_10V 0x0000
#define DAC2_BIPOLAR_5V   0x0020
#define DAC2_BIPOLAR_10V  0x0220

#define DAC37_MASK 0x0EE0
#define DAC3_UNIPOLAR_10V 0x0000
#define DAC3_BIPOLAR_5V   0x0010
#define DAC3_BIPOLAR_10V  0x0110

#define DAC4_UNIPOLAR_10V 0x0000///for analogMode.four.dac47!!
#define DAC4_BIPOLAR_5V   0x0080///not for analogMode.all!!
#define DAC4_BIPOLAR_10V  0x0880

#define DAC5_UNIPOLAR_10V 0x0000
#define DAC5_BIPOLAR_5V   0x0040
#define DAC5_BIPOLAR_10V  0x0440


#define DAC6_UNIPOLAR_10V 0x0000
#define DAC6_BIPOLAR_5V   0x0020
#define DAC6_BIPOLAR_10V  0x0220


#define DAC7_UNIPOLAR_10V 0x0000
#define DAC7_BIPOLAR_5V   0x0010
#define DAC7_BIPOLAR_10V  0x0110


#define COUNTER          0
#define WATCHDOG         1


uint8_t encControl0_buf;
uint8_t encControl1_buf;
uint8_t encControl2_buf;
uint8_t encControl3_buf;
uint8_t encControl4_buf;
uint8_t encControl5_buf;
uint8_t encControl6_buf;
uint8_t encControl7_buf;

uint8_t enc0_cmr=0x38;//initial value of enc0 within cmr
uint8_t enc1_cmr=0x38;//initial value of  enc1 within cmr
uint8_t enc2_cmr=0x38;//initial value of enc2 within cmr
uint8_t enc3_cmr=0x38;//initial value of enc3 within cmr
uint8_t enc4_cmr=0x38;//initial value of enc4 within cmr
uint8_t enc5_cmr=0x38;//initial value of enc5 within cmr
uint8_t enc6_cmr=0x38;//initial value of enc6 within cmr
uint8_t enc7_cmr=0x38;//initial value of enc7 within cmr

uint8_t enc0_idr=0x7E;
uint8_t enc1_idr=0x7E;
uint8_t enc2_idr=0x7E;
uint8_t enc3_idr=0x7E;
uint8_t enc4_idr=0x7E;
uint8_t enc5_idr=0x7E;
uint8_t enc6_idr=0x7E;
uint8_t enc7_idr=0x7E;

uint32_t udwIntEnable;
uint32_t countercontrol;
uint32_t udwIntStatus;

#define BINARY_MASK 0x1E
#define INDEX_MASK 0x1D // USED FOR INDEX POLARITY
#define INDEX_ENABLE_MASK 0x1E
#define QUADRATURE_MASK 0x07 
#define COUNT_MODE_MASK 0x19
#endif



