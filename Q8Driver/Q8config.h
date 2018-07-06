///---------------------------- FILE HEADER ----------------------------------------------------------------------------
/// component   : QUANSER Q8 CARD
/// file        : Q8config.h
/// description : Implementation for the Q8 card utility configuration functions
/// author      : Egemen Kaleli-EK,
///				  Control Technologies and Robotics Laboratory @ GYTE
/// date        : july-2008
///
///---------------------------------------------------------------------------------------------------------------------
#ifndef _Q8_CONFIG_H_
#define _Q8_CONFIG_H_

/*UTILITY CONFIGURATION FUNCTIONS'PROTOTYPES*/
void dacconfig0_unipolar_10(int);
void dacconfig0_bipolar_10(int);
void dacconfig0_bipolar_5(int);

void dacconfig1_unipolar_10(int);
void dacconfig1_bipolar_10(int);
void dacconfig1_bipolar_5(int);

void dacconfig2_unipolar_10(int);
void dacconfig2_bipolar_10(int);
void dacconfig2_bipolar_5(int);

void dacconfig3_unipolar_10(int);
void dacconfig3_bipolar_10(int);
void dacconfig3_bipolar_5(int);

void dacconfig4_unipolar_10(int);
void dacconfig4_bipolar_10(int);
void dacconfig4_bipolar_5(int);

void dacconfig5_unipolar_10(int);
void dacconfig5_bipolar_10(int);
void dacconfig5_bipolar_5(int);


void dacconfig6_unipolar_10(int);
void dacconfig6_bipolar_10(int);
void dacconfig6_bipolar_5(int);

void dacconfig7_unipolar_10(int);
void dacconfig7_bipolar_10(int);
void dacconfig7_bipolar_5(int);

void enc0_normalCount(int);
void enc0_rangelimitCount(int);
void enc0_nonrecyleCount(int);
void enc0_moduloCount(int);
void enc1_normalCount(int);
void enc1_rangelimitCount(int);
void enc1_nonrecyleCount(int);
void enc1_moduloCount(int);
void enc2_normalCount(int);
void enc2_rangelimitCount(int);
void enc2_nonrecyleCount(int);
void enc2_moduloCount(int); 
void enc3_normalCount(int);
void enc3_rangelimitCount(int);
void enc3_nonrecyleCount(int);
void enc3_moduloCount(int);
void enc4_normalCount(int);
void enc4_rangelimitCount(int);
void enc4_nonrecyleCount(int);
void enc4_moduloCount(int);
void enc5_normalCount(int);
void enc5_rangelimitCount(int);
void enc5_nonrecyleCount(int);
void enc5_moduloCount(int);  
void enc6_normalCount(int);
void enc6_rangelimitCount(int);
void enc6_nonrecyleCount(int);
void enc6_moduloCount(int); 
void enc7_normalCount(int);
void enc7_rangelimitCount(int);
void enc7_nonrecyleCount(int);
void enc7_moduloCount(int);

void enc0_nonquad(int);
void enc0_1xquad(int);
void enc0_2xquad(int);
void enc0_4xquad(int);

void enc1_nonquad(int);
void enc1_1xquad(int);
void enc1_2xquad(int);
void enc1_4xquad(int);

void enc2_nonquad(int);
void enc2_1xquad(int);
void enc2_2xquad(int);
void enc2_4xquad(int);

void enc3_nonquad(int);
void enc3_1xquad(int);
void enc3_2xquad(int);
void enc3_4xquad(int);

void enc4_nonquad(int);
void enc4_1xquad(int);
void enc4_2xquad(int);
void enc4_4xquad(int);

void enc5_nonquad(int);
void enc5_1xquad(int);
void enc5_2xquad(int);
void enc5_4xquad(int);

void enc6_nonquad(int);
void enc6_1xquad(int);
void enc6_2xquad(int);
void enc6_4xquad(int);

void enc7_nonquad(int);
void enc7_1xquad(int);
void enc7_2xquad(int);
void enc7_4xquad(int);

void enc0_enindex(int);
void enc0_disableindex(int);
void enc1_enindex(int);
void enc1_disableindex(int);
void enc2_enindex(int);
void enc2_disableindex(int);
void enc3_enindex(int);
void enc3_disableindex(int);
void enc4_enindex(int);
void enc4_disableindex(int);
void enc5_enindex(int);
void enc5_disableindex(int);
void enc6_enindex(int);
void enc6_disableindex(int);
void enc7_enindex(int);
void enc7_disableindex(int);

void enc0_posindex(int);
void  enc0_negindex(int);
 
void enc1_posindex(int);
void enc1_negindex(int);

void enc2_posindex(int); 
void enc2_negindex(int);

void enc3_posindex(int);
void enc3_negindex(int);

void enc4_posindex(int); 
void enc4_negindex(int);

void enc5_posindex(int);
void enc5_negindex(int);

void enc0_binary(int card_number);
void enc0_bcd(int card_number);

void enc1_binary(int card_number);
void enc1_bcd(int card_number);

void enc2_binary(int card_number);
void enc2_bcd(int card_number);

void enc3_binary(int card_number);
void enc3_bcd(int card_number);

void enc4_binary(int card_number);
void enc4_bcd(int card_number);

void enc5_binary(int card_number);
void enc5_bcd(int card_number);

void enc6_binary(int card_number);
void enc6_bcd(int card_number);

void enc7_binary(int card_number);
void enc7_bcd(int card_number);

static void (*const encCountMode[8][4])(int card_number)={
	 enc0_normalCount,  enc0_rangelimitCount,  enc0_nonrecyleCount,  enc0_moduloCount,
	 enc1_normalCount,  enc1_rangelimitCount,  enc1_nonrecyleCount,  enc1_moduloCount,
	 enc2_normalCount,  enc2_rangelimitCount,  enc2_nonrecyleCount,  enc2_moduloCount, 
	 enc3_normalCount,  enc3_rangelimitCount,  enc3_nonrecyleCount,  enc3_moduloCount,
	 enc4_normalCount,  enc4_rangelimitCount,  enc4_nonrecyleCount,  enc4_moduloCount,
	 enc5_normalCount,  enc5_rangelimitCount,  enc5_nonrecyleCount,  enc5_moduloCount,
	 enc6_normalCount,  enc6_rangelimitCount,  enc6_nonrecyleCount,  enc6_moduloCount, 
	 enc7_normalCount,  enc7_rangelimitCount,  enc7_nonrecyleCount,  enc7_moduloCount,
};

static void (*const encquadMode[8][4])(int card_number)={
	enc0_nonquad, enc0_1xquad, enc0_2xquad, enc0_4xquad,
	enc1_nonquad, enc1_1xquad, enc1_2xquad, enc1_4xquad,
    enc2_nonquad, enc2_1xquad, enc2_2xquad, enc2_4xquad,
    enc3_nonquad, enc3_1xquad, enc3_2xquad, enc3_4xquad,
    enc4_nonquad, enc4_1xquad, enc4_2xquad, enc4_4xquad,
    enc5_nonquad, enc5_1xquad, enc5_2xquad, enc5_4xquad,
    enc6_nonquad, enc6_1xquad, enc6_2xquad, enc6_4xquad,
    enc7_nonquad, enc7_1xquad, enc7_2xquad, enc7_4xquad,
};

static void (*const   indexendisable[8][2])(int card_number)={
	 enc0_enindex, enc0_disableindex,
	 enc1_enindex, enc1_disableindex,
	 enc2_enindex, enc2_disableindex,
	 enc3_enindex, enc3_disableindex,
	 enc4_enindex, enc4_disableindex,
	 enc5_enindex, enc5_disableindex,
	 enc6_enindex, enc6_disableindex,
	 enc7_enindex, enc7_disableindex,
};


static void (*const   indexpolarity[8][2])(int card_number)={
	 enc0_posindex,  enc0_negindex,
	 enc1_posindex,  enc1_negindex,
	 enc2_posindex,  enc2_negindex,
	 enc3_posindex,  enc3_negindex,
	 enc4_posindex,  enc4_negindex,
	 enc5_posindex, enc5_negindex,
};

static void (*const   bcdorbinary[8][2])(int card_number)={
	 enc0_binary,  enc0_bcd,
	 enc1_binary,  enc1_bcd,
	 enc2_binary,  enc2_bcd,
	 enc3_binary,  enc3_bcd,
	 enc4_binary,  enc4_bcd,
	 enc5_binary,  enc5_bcd,
	 enc6_binary,  enc6_bcd,
	 enc7_binary,  enc7_bcd,

};
static void (*const dacConfigs[8][3])(int card_number)={
	dacconfig0_unipolar_10, dacconfig0_bipolar_5, dacconfig0_bipolar_10,
	dacconfig1_unipolar_10, dacconfig1_bipolar_5, dacconfig1_bipolar_10,
    dacconfig2_unipolar_10, dacconfig2_bipolar_5, dacconfig2_bipolar_10,
    dacconfig3_unipolar_10, dacconfig3_bipolar_5, dacconfig3_bipolar_10,
    dacconfig4_unipolar_10, dacconfig4_bipolar_5, dacconfig4_bipolar_10,
    dacconfig5_unipolar_10, dacconfig5_bipolar_5, dacconfig5_bipolar_10,
    dacconfig6_unipolar_10, dacconfig6_bipolar_5, dacconfig6_bipolar_10,
    dacconfig7_unipolar_10, dacconfig7_bipolar_5, dacconfig7_bipolar_10,
};

///========================== FUNCTION HEADERS OF encX_binary FUNCTIONS================================================
/// Name        : encX_binary
/// Input       : cardNum - PCI memory region that is mapped to Q8 card memory 
/// Output      : None
/// Return      : an integer value(not used)
/// Description : Configures  the encoder channel of which number specified by "X" as binary mode
///                                
///=====================================================================================================================
void enc0_binary(int cardNum){
	enc0_cmr=(enc0_cmr  & BINARY_MASK) | ENC_ONE_CHANNEL | ENC_CMR_REGISTER ;
	iowrite8(enc0_cmr , &(q8Con->Q8reg->encoderControl.one.enc0));
} 
 
void enc1_binary(int cardNum){
	enc1_cmr=(enc1_cmr  & BINARY_MASK) | ENC_ONE_CHANNEL | ENC_CMR_REGISTER ;
	iowrite8(enc1_cmr , &(q8Con->Q8reg->encoderControl.one.enc1));
} 
 
void enc2_binary(int cardNum){
	enc2_cmr=(enc2_cmr  & BINARY_MASK) | ENC_ONE_CHANNEL | ENC_CMR_REGISTER ;
	iowrite8(enc2_cmr , &(q8Con->Q8reg->encoderControl.one.enc2));
} 
 
void enc3_binary(int cardNum){
	enc3_cmr=(enc3_cmr  & BINARY_MASK) | ENC_ONE_CHANNEL | ENC_CMR_REGISTER ;
	iowrite8(enc3_cmr , &(q8Con->Q8reg->encoderControl.one.enc3));
} 
 
void enc4_binary(int cardNum){
	enc4_cmr=(enc4_cmr  & BINARY_MASK) | ENC_ONE_CHANNEL | ENC_CMR_REGISTER ;
	iowrite8(enc4_cmr , &(q8Con->Q8reg->encoderControl.one.enc4));
} 

void enc5_binary(int cardNum){
	enc5_cmr=(enc5_cmr  & BINARY_MASK) | ENC_ONE_CHANNEL | ENC_CMR_REGISTER ;
	iowrite8(enc5_cmr , &(q8Con->Q8reg->encoderControl.one.enc5));
} 

void enc6_binary(int cardNum){
	enc6_cmr=(enc6_cmr  & BINARY_MASK) | ENC_ONE_CHANNEL | ENC_CMR_REGISTER ;
	iowrite8(enc6_cmr , &(q8Con->Q8reg->encoderControl.one.enc6));
} 

void enc7_binary(int cardNum){
	enc7_cmr=(enc7_cmr  & BINARY_MASK) | ENC_ONE_CHANNEL | ENC_CMR_REGISTER ;
	iowrite8(enc7_cmr , &(q8Con->Q8reg->encoderControl.one.enc7));
} 
 
///========================== FUNCTION HEADERS OF encX_bcd FUNCTIONS====================================================
/// Name        : encX_bcd
/// Input       : cardNum - PCI memory region that is mapped to Q8 card memory 
/// Output      : None
/// Return      : None
/// Description : Configures  the encoder channel of which number specified by "X" as bcd mode
///                                
///=====================================================================================================================
void enc0_bcd(int cardNum){
	enc0_cmr=(enc0_cmr  & BINARY_MASK) | ENC_ONE_CHANNEL | ENC_CMR_REGISTER | ENC_CMR_BCD;
	iowrite8(enc0_cmr, &(q8Con->Q8reg->encoderControl.one.enc0));
} 

void enc1_bcd(int cardNum){
	enc1_cmr=(enc1_cmr  & BINARY_MASK) | ENC_ONE_CHANNEL | ENC_CMR_REGISTER | ENC_CMR_BCD;
	iowrite8(enc1_cmr, &(q8Con->Q8reg->encoderControl.one.enc1));
} 
 
void enc2_bcd(int cardNum){
	enc2_cmr=(enc2_cmr  & BINARY_MASK) | ENC_ONE_CHANNEL | ENC_CMR_REGISTER | ENC_CMR_BCD;
	iowrite8(enc2_cmr, &(q8Con->Q8reg->encoderControl.one.enc2));
} 

void enc3_bcd(int cardNum){
	enc3_cmr=(enc3_cmr  & BINARY_MASK) | ENC_ONE_CHANNEL | ENC_CMR_REGISTER | ENC_CMR_BCD;
	iowrite8(enc3_cmr, &(q8Con->Q8reg->encoderControl.one.enc3));
} 

void enc4_bcd(int cardNum){
	enc4_cmr=(enc4_cmr  & BINARY_MASK) | ENC_ONE_CHANNEL | ENC_CMR_REGISTER | ENC_CMR_BCD;
	iowrite8(enc4_cmr, &(q8Con->Q8reg->encoderControl.one.enc4));
} 

void enc5_bcd(int cardNum){
	enc5_cmr=(enc5_cmr  & BINARY_MASK) | ENC_ONE_CHANNEL | ENC_CMR_REGISTER | ENC_CMR_BCD;
	iowrite8(enc5_cmr, &(q8Con->Q8reg->encoderControl.one.enc5));
} 

void enc6_bcd(int cardNum){
	enc6_cmr=(enc6_cmr  & BINARY_MASK) | ENC_ONE_CHANNEL | ENC_CMR_REGISTER | ENC_CMR_BCD;
	iowrite8(enc6_cmr, &(q8Con->Q8reg->encoderControl.one.enc6));
} 
 
void enc7_bcd(int cardNum){
	enc7_cmr=(enc7_cmr  & BINARY_MASK) | ENC_ONE_CHANNEL | ENC_CMR_REGISTER | ENC_CMR_BCD;
	iowrite8(enc7_cmr, &(q8Con->Q8reg->encoderControl.one.enc7));
} 
 
///========================== FUNCTION HEADERS OF encX_posindex FUNCTIONS===============================================
/// Name        : encX_posindex
/// Input       : cardNum - PCI memory region that is mapped to Q8 card memory 
/// Output      : None
/// Return      : None
/// Description : Configures  the encoder channel of which number specified by "X" with positive index
///                                
///=====================================================================================================================
void enc0_posindex(int cardNum){
	enc0_idr=(enc0_idr & INDEX_MASK) | ENC_ONE_CHANNEL | ENC_IDR_REGISTER | ENC_IDR_POS_INDEX ;
	iowrite8(enc0_idr, &(q8Con->Q8reg->encoderControl.one.enc0));
}

void enc1_posindex(int cardNum){
	enc1_idr=(enc1_idr & INDEX_MASK) | ENC_ONE_CHANNEL | ENC_IDR_REGISTER | ENC_IDR_POS_INDEX ;
	iowrite8(enc1_idr, &(q8Con->Q8reg->encoderControl.one.enc1));
}

void enc2_posindex(int cardNum){
	enc2_idr=(enc2_idr & INDEX_MASK) | ENC_ONE_CHANNEL | ENC_IDR_REGISTER | ENC_IDR_POS_INDEX ;
	iowrite8(enc2_idr, &(q8Con->Q8reg->encoderControl.one.enc2));
}

void enc3_posindex(int cardNum){
	enc3_idr=(enc3_idr & INDEX_MASK) | ENC_ONE_CHANNEL | ENC_IDR_REGISTER | ENC_IDR_POS_INDEX ;
	iowrite8(enc3_idr, &(q8Con->Q8reg->encoderControl.one.enc3));
}

void enc4_posindex(int cardNum){
	enc4_idr=(enc4_idr & INDEX_MASK) | ENC_ONE_CHANNEL | ENC_IDR_REGISTER | ENC_IDR_POS_INDEX ;
	iowrite8(enc4_idr, &(q8Con->Q8reg->encoderControl.one.enc4));
}

void enc5_posindex(int cardNum){
	enc5_idr=(enc5_idr & INDEX_MASK) | ENC_ONE_CHANNEL | ENC_IDR_REGISTER | ENC_IDR_POS_INDEX ;
	iowrite8(enc5_idr, &(q8Con->Q8reg->encoderControl.one.enc5));
}

void enc6_posindex(int cardNum){
	enc6_idr=(enc6_idr & INDEX_MASK) | ENC_ONE_CHANNEL | ENC_IDR_REGISTER | ENC_IDR_POS_INDEX ;
	iowrite8(enc6_idr, &(q8Con->Q8reg->encoderControl.one.enc6));
}

void enc7_posindex(int cardNum){
	enc7_idr=(enc7_idr & INDEX_MASK) | ENC_ONE_CHANNEL | ENC_IDR_REGISTER | ENC_IDR_POS_INDEX ;
	iowrite8(enc7_idr, &(q8Con->Q8reg->encoderControl.one.enc7));
}

///========================== FUNCTION HEADERS OF encX_negindex FUNCTIONS===============================================
/// Name        : encX_negindex
/// Input       : cardNum - PCI memory region that is mapped to Q8 card memory 
/// Output      : None
/// Return      : None
/// Description : Configures  the encoder channel of which number is specified by "X" with negative index
///                                
///=====================================================================================================================
void enc0_negindex(int cardNum){
	enc0_idr=(enc0_idr & INDEX_MASK) | ENC_ONE_CHANNEL | ENC_IDR_REGISTER;
	iowrite8(enc0_idr, &(q8Con->Q8reg->encoderControl.one.enc0));
}

void enc1_negindex(int cardNum){
	enc1_idr=(enc1_idr & INDEX_MASK) | ENC_ONE_CHANNEL | ENC_IDR_REGISTER;
	iowrite8(enc1_idr, &(q8Con->Q8reg->encoderControl.one.enc1));
}

void enc2_negindex(int cardNum){
	enc2_idr=(enc2_idr & INDEX_MASK) | ENC_ONE_CHANNEL | ENC_IDR_REGISTER;
	iowrite8(enc2_idr, &(q8Con->Q8reg->encoderControl.one.enc2));
}

void enc3_negindex(int cardNum){
	enc3_idr=(enc3_idr & INDEX_MASK) | ENC_ONE_CHANNEL | ENC_IDR_REGISTER;
	iowrite8(enc3_idr, &(q8Con->Q8reg->encoderControl.one.enc3));
}

void enc4_negindex(int cardNum){
	enc4_idr=(enc4_idr & INDEX_MASK) | ENC_ONE_CHANNEL | ENC_IDR_REGISTER;
	iowrite8(enc4_idr, &(q8Con->Q8reg->encoderControl.one.enc4));
}

void enc5_negindex(int cardNum){
	enc5_idr=(enc5_idr & INDEX_MASK) | ENC_ONE_CHANNEL | ENC_IDR_REGISTER;
	iowrite8(enc5_idr, &(q8Con->Q8reg->encoderControl.one.enc5));
}

void enc6_negindex(int cardNum){
	enc6_idr=(enc6_idr & INDEX_MASK) | ENC_ONE_CHANNEL | ENC_IDR_REGISTER;
	iowrite8(enc6_idr, &(q8Con->Q8reg->encoderControl.one.enc6));
}

void enc7_negindex(int cardNum){
	enc7_idr=(enc7_idr & INDEX_MASK) | ENC_ONE_CHANNEL | ENC_IDR_REGISTER;
	iowrite8(enc7_idr, &(q8Con->Q8reg->encoderControl.one.enc7));
}

///========================== FUNCTION HEADERS OF encX_enindex FUNCTIONS===============================================
/// Name        : encX_posindex
/// Input       : cardNum - PCI memory region that is mapped to Q8 card memory 
/// Output      : None
/// Return      : None
/// Description : Enables index feature of  the encoder channel of which number is specified by "X" 
///                                
///=====================================================================================================================
void enc0_enindex(int cardNum){
	enc0_idr=(enc0_idr & INDEX_ENABLE_MASK) | ENC_ONE_CHANNEL | ENC_IDR_REGISTER | ENC_IDR_ENABLE_INDEX;
	iowrite8(enc0_idr, &(q8Con->Q8reg->encoderControl.one.enc0));
}

void enc1_enindex(int cardNum){
	enc1_idr=(enc1_idr & INDEX_ENABLE_MASK) | ENC_ONE_CHANNEL | ENC_IDR_REGISTER | ENC_IDR_ENABLE_INDEX;
	iowrite8(enc1_idr, &(q8Con->Q8reg->encoderControl.one.enc1));
}

void enc2_enindex(int cardNum){
	enc2_idr=(enc2_idr & INDEX_ENABLE_MASK) | ENC_ONE_CHANNEL | ENC_IDR_REGISTER | ENC_IDR_ENABLE_INDEX;
	iowrite8(enc2_idr, &(q8Con->Q8reg->encoderControl.one.enc2));
}

void enc3_enindex(int cardNum){
	enc3_idr=(enc3_idr & INDEX_ENABLE_MASK) | ENC_ONE_CHANNEL | ENC_IDR_REGISTER | ENC_IDR_ENABLE_INDEX;
	iowrite8(enc3_idr, &(q8Con->Q8reg->encoderControl.one.enc3));
}

void enc4_enindex(int cardNum){
	enc4_idr=(enc4_idr & INDEX_ENABLE_MASK) | ENC_ONE_CHANNEL | ENC_IDR_REGISTER | ENC_IDR_ENABLE_INDEX;
	iowrite8(enc4_idr, &(q8Con->Q8reg->encoderControl.one.enc4));
}

void enc5_enindex(int cardNum){
	enc5_idr=(enc5_idr & INDEX_ENABLE_MASK) | ENC_ONE_CHANNEL | ENC_IDR_REGISTER | ENC_IDR_ENABLE_INDEX;
	iowrite8(enc5_idr, &(q8Con->Q8reg->encoderControl.one.enc5));
}

void enc6_enindex(int cardNum){
	enc6_idr=(enc6_idr & INDEX_ENABLE_MASK) | ENC_ONE_CHANNEL | ENC_IDR_REGISTER | ENC_IDR_ENABLE_INDEX;
	iowrite8(enc6_idr, &(q8Con->Q8reg->encoderControl.one.enc6));
}

void enc7_enindex(int cardNum){
	enc7_idr=(enc7_idr & INDEX_ENABLE_MASK) | ENC_ONE_CHANNEL | ENC_IDR_REGISTER | ENC_IDR_ENABLE_INDEX;
	iowrite8(enc7_idr, &(q8Con->Q8reg->encoderControl.one.enc7));
}

///========================== FUNCTION HEADERS OF encX_disableindex FUNCTIONS==========================================
/// Name        : encX_disableindex
/// Input       : cardNum - PCI memory region that is mapped to Q8 card memory 
/// Output      : None
/// Return      : None
/// Description : Disables index feature of  the encoder channel of which number is specified by "X" 
///                                
///=====================================================================================================================
void enc0_disableindex(int cardNum){ 
	enc0_idr=(enc0_idr & INDEX_ENABLE_MASK) | ENC_ONE_CHANNEL | ENC_IDR_REGISTER;
	iowrite8(enc0_idr, &(q8Con->Q8reg->encoderControl.one.enc0));
}

void enc1_disableindex(int cardNum){
	enc1_idr=(enc1_idr & INDEX_ENABLE_MASK) | ENC_ONE_CHANNEL | ENC_IDR_REGISTER;
	iowrite8(enc1_idr, &(q8Con->Q8reg->encoderControl.one.enc1));
}

void enc2_disableindex(int cardNum){
	enc2_idr=(enc2_idr & INDEX_ENABLE_MASK) | ENC_ONE_CHANNEL | ENC_IDR_REGISTER;
	iowrite8(enc2_idr, &(q8Con->Q8reg->encoderControl.one.enc2));
}

void enc3_disableindex(int cardNum){
	enc3_idr=(enc3_idr & INDEX_ENABLE_MASK) | ENC_ONE_CHANNEL | ENC_IDR_REGISTER;
	iowrite8(enc3_idr, &(q8Con->Q8reg->encoderControl.one.enc3));
}

void enc4_disableindex(int cardNum){
	enc4_idr=(enc4_idr & INDEX_ENABLE_MASK) | ENC_ONE_CHANNEL | ENC_IDR_REGISTER;
	iowrite8(enc4_idr, &(q8Con->Q8reg->encoderControl.one.enc4));
}

void enc5_disableindex(int cardNum){
	enc5_idr=(enc5_idr & INDEX_ENABLE_MASK) | ENC_ONE_CHANNEL | ENC_IDR_REGISTER;
	iowrite8(enc5_idr, &(q8Con->Q8reg->encoderControl.one.enc5));
}

void enc6_disableindex(int cardNum){
	enc6_idr=(enc6_idr & INDEX_ENABLE_MASK) | ENC_ONE_CHANNEL | ENC_IDR_REGISTER;
	iowrite8(enc6_idr, &(q8Con->Q8reg->encoderControl.one.enc6));
}

void enc7_disableindex(int cardNum){
	enc1_idr=(enc7_idr & INDEX_ENABLE_MASK) | ENC_ONE_CHANNEL | ENC_IDR_REGISTER;
	iowrite8(enc7_idr, &(q8Con->Q8reg->encoderControl.one.enc7));
}

///========================== FUNCTION HEADERS OF encX_nonquadrature FUNCTIONS==========================================
/// Name        : encX_nonquad
/// Input       : cardNum - PCI memory region that is mapped to Q8 card memory 
/// Output      : None
/// Return      : None
/// Description : Configures  the encoder channel of which number is specified by "X" as nonquadrature
///                                
///=====================================================================================================================
void enc0_nonquad(int cardNum){
	enc0_cmr=(QUADRATURE_MASK & enc0_cmr) | ENC_ONE_CHANNEL | ENC_CMR_REGISTER | ENC_CMR_NONQUADRATURE;
	iowrite8(enc0_cmr, &(q8Con->Q8reg->encoderControl.one.enc0));
}

void enc1_nonquad(int cardNum){
	enc1_cmr=(QUADRATURE_MASK & enc1_cmr) | ENC_ONE_CHANNEL | ENC_CMR_REGISTER | ENC_CMR_NONQUADRATURE;
	iowrite8(enc1_cmr, &(q8Con->Q8reg->encoderControl.one.enc1));
}

void enc2_nonquad(int cardNum){
	enc2_cmr=(QUADRATURE_MASK & enc2_cmr) | ENC_ONE_CHANNEL | ENC_CMR_REGISTER | ENC_CMR_NONQUADRATURE;
	iowrite8(enc2_cmr, &(q8Con->Q8reg->encoderControl.one.enc2));
}

void enc3_nonquad(int cardNum){ 
	enc3_cmr=(QUADRATURE_MASK & enc3_cmr) | ENC_ONE_CHANNEL | ENC_CMR_REGISTER | ENC_CMR_NONQUADRATURE;
	iowrite8(enc3_cmr, &(q8Con->Q8reg->encoderControl.one.enc3));
}

void enc4_nonquad(int cardNum){ 
	enc4_cmr=(QUADRATURE_MASK & enc4_cmr) | ENC_ONE_CHANNEL | ENC_CMR_REGISTER | ENC_CMR_NONQUADRATURE;
	iowrite8(enc4_cmr, &(q8Con->Q8reg->encoderControl.one.enc4));
}

void enc5_nonquad(int cardNum){ 
	enc5_cmr=(QUADRATURE_MASK & enc5_cmr) | ENC_ONE_CHANNEL | ENC_CMR_REGISTER | ENC_CMR_NONQUADRATURE;
	iowrite8(enc5_cmr, &(q8Con->Q8reg->encoderControl.one.enc5));
}

void enc6_nonquad(int cardNum){
	enc6_cmr=(QUADRATURE_MASK & enc6_cmr) | ENC_ONE_CHANNEL | ENC_CMR_REGISTER | ENC_CMR_NONQUADRATURE;
	iowrite8(enc6_cmr, &(q8Con->Q8reg->encoderControl.one.enc6));
}

void enc7_nonquad(int cardNum){
	enc7_cmr=(QUADRATURE_MASK & enc7_cmr) | ENC_ONE_CHANNEL | ENC_CMR_REGISTER | ENC_CMR_NONQUADRATURE;
	iowrite8(enc7_cmr, &(q8Con->Q8reg->encoderControl.one.enc7));
}

///========================== FUNCTION HEADERS OF encX_1xquad FUNCTIONS=================================================
/// Name        : encX_1xquad
/// Input       : cardNum - PCI memory region that is mapped to Q8 card memory 
/// Output      : None
/// Return      : None
/// Description : Configures  the encoder channel of which number is specified by "X" as 1x quadrature
///                                
///=====================================================================================================================
void enc0_1xquad(int cardNum){
	enc0_cmr=(QUADRATURE_MASK & enc0_cmr) | ENC_ONE_CHANNEL | ENC_CMR_REGISTER | ENC_CMR_QUADRATURE_1X;
	iowrite8(enc0_cmr, &(q8Con->Q8reg->encoderControl.one.enc0));
}

void enc1_1xquad(int cardNum){
	enc1_cmr=(QUADRATURE_MASK & enc1_cmr) | ENC_ONE_CHANNEL | ENC_CMR_REGISTER | ENC_CMR_QUADRATURE_1X;
	iowrite8(enc1_cmr, &(q8Con->Q8reg->encoderControl.one.enc1));
}

void enc2_1xquad(int cardNum){
	enc2_cmr=(QUADRATURE_MASK & enc2_cmr) | ENC_ONE_CHANNEL | ENC_CMR_REGISTER | ENC_CMR_QUADRATURE_1X;
	iowrite8(enc2_cmr, &(q8Con->Q8reg->encoderControl.one.enc2));
}

void enc3_1xquad(int cardNum){
	enc3_cmr=(QUADRATURE_MASK & enc3_cmr) | ENC_ONE_CHANNEL | ENC_CMR_REGISTER | ENC_CMR_QUADRATURE_1X;
	iowrite8(enc3_cmr, &(q8Con->Q8reg->encoderControl.one.enc3));
}

void enc4_1xquad(int cardNum){
	enc4_cmr=(QUADRATURE_MASK & enc4_cmr) | ENC_ONE_CHANNEL | ENC_CMR_REGISTER | ENC_CMR_QUADRATURE_1X;
	iowrite8(enc4_cmr, &(q8Con->Q8reg->encoderControl.one.enc4));
}

void enc5_1xquad(int cardNum){
	enc5_cmr=(QUADRATURE_MASK & enc5_cmr) | ENC_ONE_CHANNEL | ENC_CMR_REGISTER | ENC_CMR_QUADRATURE_1X;
	iowrite8(enc5_cmr, &(q8Con->Q8reg->encoderControl.one.enc5));
}

void enc6_1xquad(int cardNum){
	enc6_cmr=(QUADRATURE_MASK & enc6_cmr) | ENC_ONE_CHANNEL | ENC_CMR_REGISTER | ENC_CMR_QUADRATURE_1X;
	iowrite8(enc6_cmr, &(q8Con->Q8reg->encoderControl.one.enc6));
}


void enc7_1xquad(int cardNum){
	enc7_cmr=(QUADRATURE_MASK & enc7_cmr) | ENC_ONE_CHANNEL | ENC_CMR_REGISTER | ENC_CMR_QUADRATURE_1X;
	iowrite8(enc7_cmr, &(q8Con->Q8reg->encoderControl.one.enc7));
}

///========================== FUNCTION HEADERS OF encX_2xquad FUNCTIONS=================================================
/// Name        : encX_2xquad
/// Input       : cardNum - PCI memory region that is mapped to Q8 card memory 
/// Output      : None
/// Return      : None
/// Description : Configures  the encoder  channel of which number is specified by "X" as 2x quadrature
///                                
///=====================================================================================================================
void enc0_2xquad(int cardNum){
	enc0_cmr=(QUADRATURE_MASK & enc0_cmr) | ENC_ONE_CHANNEL | ENC_CMR_REGISTER | ENC_CMR_QUADRATURE_2X ;
	iowrite8(enc0_cmr, &(q8Con->Q8reg->encoderControl.one.enc0));
}

void enc1_2xquad(int cardNum){
	enc1_cmr=(QUADRATURE_MASK & enc1_cmr) | ENC_ONE_CHANNEL | ENC_CMR_REGISTER | ENC_CMR_QUADRATURE_2X ;
	iowrite8(enc1_cmr, &(q8Con->Q8reg->encoderControl.one.enc1));
}

void enc2_2xquad(int cardNum){ 
	enc2_cmr=(QUADRATURE_MASK & enc2_cmr) | ENC_ONE_CHANNEL | ENC_CMR_REGISTER | ENC_CMR_QUADRATURE_2X ;
	iowrite8(enc2_cmr, &(q8Con->Q8reg->encoderControl.one.enc2));
}

void enc3_2xquad(int cardNum){
	enc3_cmr=(QUADRATURE_MASK & enc3_cmr) | ENC_ONE_CHANNEL | ENC_CMR_REGISTER | ENC_CMR_QUADRATURE_2X ;
	iowrite8(enc3_cmr, &(q8Con->Q8reg->encoderControl.one.enc3));
}

void enc4_2xquad(int cardNum){
	enc4_cmr=(QUADRATURE_MASK & enc4_cmr) | ENC_ONE_CHANNEL | ENC_CMR_REGISTER | ENC_CMR_QUADRATURE_2X ;
	iowrite8(enc4_cmr, &(q8Con->Q8reg->encoderControl.one.enc4));
}

void enc5_2xquad(int cardNum){ 
	enc5_cmr=(QUADRATURE_MASK & enc5_cmr) | ENC_ONE_CHANNEL | ENC_CMR_REGISTER | ENC_CMR_QUADRATURE_2X ;
	iowrite8(enc5_idr, &(q8Con->Q8reg->encoderControl.one.enc5));
}

void enc6_2xquad(int cardNum){
	enc6_cmr=(QUADRATURE_MASK & enc6_cmr) | ENC_ONE_CHANNEL | ENC_CMR_REGISTER | ENC_CMR_QUADRATURE_2X ;
	iowrite8(enc6_cmr, &(q8Con->Q8reg->encoderControl.one.enc6));
}

void enc7_2xquad(int cardNum){
	enc7_cmr=(QUADRATURE_MASK & enc7_cmr) | ENC_ONE_CHANNEL | ENC_CMR_REGISTER | ENC_CMR_QUADRATURE_2X ;
	iowrite8(enc7_cmr, &(q8Con->Q8reg->encoderControl.one.enc7));
}

///========================== FUNCTION HEADERS OF encX_4xquad FUNCTIONS=================================================
/// Name        : encX_4xquad
/// Input       : cardNum - PCI memory region that is mapped to Q8 card memory 
/// Output      : None
/// Return      : None
/// Description : Configures  the encoder channel of which number is specified by "X" as 4x quadrature
///                                
///=====================================================================================================================
void enc0_4xquad(int cardNum){ 
	enc0_cmr=(QUADRATURE_MASK & enc0_cmr) | ENC_ONE_CHANNEL | ENC_CMR_REGISTER | ENC_CMR_QUADRATURE_4X ;
	iowrite8(enc0_cmr, &(q8Con->Q8reg->encoderControl.one.enc0));
}

void enc1_4xquad(int cardNum){ 
	enc1_cmr=(QUADRATURE_MASK & enc1_cmr) | ENC_ONE_CHANNEL | ENC_CMR_REGISTER | ENC_CMR_QUADRATURE_4X ;
	iowrite8(enc1_cmr, &(q8Con->Q8reg->encoderControl.one.enc1));
}

void enc2_4xquad(int cardNum){ 
	enc2_cmr=(QUADRATURE_MASK & enc2_cmr) | ENC_ONE_CHANNEL | ENC_CMR_REGISTER | ENC_CMR_QUADRATURE_4X ;
	iowrite8(enc2_cmr, &(q8Con->Q8reg->encoderControl.one.enc2));
}

void enc3_4xquad(int cardNum){ 
	enc3_cmr=(QUADRATURE_MASK & enc3_cmr) | ENC_ONE_CHANNEL | ENC_CMR_REGISTER | ENC_CMR_QUADRATURE_4X ;
	iowrite8(enc3_cmr, &(q8Con->Q8reg->encoderControl.one.enc3));
}

void enc4_4xquad(int cardNum){
	enc4_cmr=(QUADRATURE_MASK & enc4_cmr) | ENC_ONE_CHANNEL | ENC_CMR_REGISTER | ENC_CMR_QUADRATURE_4X ;
	iowrite8(enc4_cmr, &(q8Con->Q8reg->encoderControl.one.enc4));
}

void enc5_4xquad(int cardNum){ 
	enc5_cmr=(QUADRATURE_MASK & enc5_cmr) | ENC_ONE_CHANNEL | ENC_CMR_REGISTER | ENC_CMR_QUADRATURE_4X ;
	iowrite8(enc5_cmr, &(q8Con->Q8reg->encoderControl.one.enc5));
}

void enc6_4xquad(int cardNum){ 
	enc6_cmr=(QUADRATURE_MASK & enc6_cmr) | ENC_ONE_CHANNEL | ENC_CMR_REGISTER | ENC_CMR_QUADRATURE_4X ;
	iowrite8(enc6_cmr, &(q8Con->Q8reg->encoderControl.one.enc6));
}

void enc7_4xquad(int cardNum){ 
	enc7_cmr=(QUADRATURE_MASK & enc7_cmr) | ENC_ONE_CHANNEL | ENC_CMR_REGISTER | ENC_CMR_QUADRATURE_4X ;
	iowrite8(enc7_cmr, &(q8Con->Q8reg->encoderControl.one.enc7));
}

///========================== FUNCTION HEADERS OF encX_normalCount FUNCTIONS===========================================
/// Name        : encX_normalCount
/// Input       : cardNum - PCI memory region that is mapped to Q8 card memory 
/// Output      : None
/// Return      : None
/// Description : Configures  the encoder channel of which number is specified by "X" as normal count.
///                                
///=====================================================================================================================
void enc0_normalCount(int cardNum){
	enc0_cmr=(COUNT_MODE_MASK & enc0_cmr) | ENC_ONE_CHANNEL | ENC_CMR_REGISTER | ENC_CMR_NORMAL;
	iowrite8(enc0_cmr, &(q8Con->Q8reg->encoderControl.one.enc0));
}

void enc1_normalCount(int cardNum){
	enc1_cmr=(COUNT_MODE_MASK & enc1_cmr) | ENC_ONE_CHANNEL | ENC_CMR_REGISTER | ENC_CMR_NORMAL;
	iowrite8(enc1_cmr, &(q8Con->Q8reg->encoderControl.one.enc1));
}

void enc2_normalCount(int cardNum){
	enc2_cmr=(COUNT_MODE_MASK & enc2_cmr) | ENC_ONE_CHANNEL | ENC_CMR_REGISTER | ENC_CMR_NORMAL;
	iowrite8(enc2_cmr, &(q8Con->Q8reg->encoderControl.one.enc2));
}

void enc3_normalCount(int cardNum){
	enc3_cmr=(COUNT_MODE_MASK & enc3_cmr) | ENC_ONE_CHANNEL | ENC_CMR_REGISTER | ENC_CMR_NORMAL;
	iowrite8(enc3_cmr, &(q8Con->Q8reg->encoderControl.one.enc3));
}

void enc4_normalCount(int cardNum){
	enc4_cmr=(COUNT_MODE_MASK & enc4_cmr) | ENC_ONE_CHANNEL | ENC_CMR_REGISTER | ENC_CMR_NORMAL;
	iowrite8(enc4_cmr, &(q8Con->Q8reg->encoderControl.one.enc4));
}

void enc5_normalCount(int cardNum){
	enc5_cmr=(COUNT_MODE_MASK & enc5_cmr) | ENC_ONE_CHANNEL | ENC_CMR_REGISTER | ENC_CMR_NORMAL;
	iowrite8(enc5_cmr, &(q8Con->Q8reg->encoderControl.one.enc5));;
}

void enc6_normalCount(int cardNum){
	enc6_cmr=(COUNT_MODE_MASK & enc6_cmr) | ENC_ONE_CHANNEL | ENC_CMR_REGISTER | ENC_CMR_NORMAL;
	iowrite8(enc6_cmr, &(q8Con->Q8reg->encoderControl.one.enc6));
}

void enc7_normalCount(int cardNum){
	enc7_cmr=(COUNT_MODE_MASK & enc7_cmr) | ENC_ONE_CHANNEL | ENC_CMR_REGISTER | ENC_CMR_NORMAL;
	iowrite8(enc7_cmr, &(q8Con->Q8reg->encoderControl.one.enc7));
}

///========================== FUNCTION HEADERS OF encX_rangelimitCount FUNCTIONS========================================
/// Name        : encX_rangelimitCount 
/// Input       : cardNum - PCI memory region that is mapped to Q8 card memory 
/// Output      : None
/// Return      : None
/// Description : Configures  the encoder channel of which number is specified by "X" as range limit count
///                                
///=====================================================================================================================
void  enc0_rangelimitCount(int cardNum){
 	enc0_cmr=(COUNT_MODE_MASK & enc0_cmr) | ENC_ONE_CHANNEL | ENC_CMR_REGISTER |ENC_CMR_RANGE;
 	iowrite8(enc0_cmr, &(q8Con->Q8reg->encoderControl.one.enc0));
}

void  enc1_rangelimitCount(int cardNum){
	enc1_cmr=(COUNT_MODE_MASK & enc1_cmr) | ENC_ONE_CHANNEL | ENC_CMR_REGISTER |ENC_CMR_RANGE;
	iowrite8(enc1_cmr, &(q8Con->Q8reg->encoderControl.one.enc1));
}

void  enc2_rangelimitCount(int cardNum){
	enc2_cmr=(COUNT_MODE_MASK & enc2_cmr) | ENC_ONE_CHANNEL | ENC_CMR_REGISTER |ENC_CMR_RANGE;
	iowrite8(enc2_cmr, &(q8Con->Q8reg->encoderControl.one.enc2));
}

void  enc3_rangelimitCount(int cardNum){
	enc3_cmr=(COUNT_MODE_MASK & enc3_cmr) | ENC_ONE_CHANNEL | ENC_CMR_REGISTER |ENC_CMR_RANGE;
	iowrite8(enc3_cmr, &(q8Con->Q8reg->encoderControl.one.enc3));
}

void  enc4_rangelimitCount(int cardNum){
	enc4_cmr=(COUNT_MODE_MASK & enc4_cmr) | ENC_ONE_CHANNEL | ENC_CMR_REGISTER |ENC_CMR_RANGE;
	iowrite8(enc4_cmr, &(q8Con->Q8reg->encoderControl.one.enc4));
}

void  enc5_rangelimitCount(int cardNum){
	enc5_cmr=(COUNT_MODE_MASK & enc5_cmr) | ENC_ONE_CHANNEL | ENC_CMR_REGISTER |ENC_CMR_RANGE;
	iowrite8(enc5_cmr, &(q8Con->Q8reg->encoderControl.one.enc5));
}

void  enc6_rangelimitCount(int cardNum){
	enc6_cmr=(COUNT_MODE_MASK & enc6_cmr) | ENC_ONE_CHANNEL | ENC_CMR_REGISTER |ENC_CMR_RANGE;
	iowrite8(enc6_cmr, &(q8Con->Q8reg->encoderControl.one.enc6));
}

void  enc7_rangelimitCount(int cardNum){
	enc7_cmr=(COUNT_MODE_MASK & enc7_cmr) | ENC_ONE_CHANNEL | ENC_CMR_REGISTER |ENC_CMR_RANGE;
	iowrite8(enc7_cmr, &(q8Con->Q8reg->encoderControl.one.enc7));
}

///========================== FUNCTION HEADERS OF encX_nonrecycleCount FUNCTIONS========================================
/// Name        : encX_nonrecycleCount
/// Input       : cardNum - PCI memory region that is mapped to Q8 card memory 
/// Output      : None
/// Return      : None
/// Description : Configures  the encoder channel of which number is specified by "X" as non recycle count
///                                
///=====================================================================================================================
void  enc0_nonrecyleCount(int cardNum){
	enc0_cmr=(COUNT_MODE_MASK & enc0_cmr) | ENC_ONE_CHANNEL | ENC_CMR_REGISTER | ENC_CMR_NONRECYCLE;
	iowrite8(enc0_cmr, &(q8Con->Q8reg->encoderControl.one.enc0));
}

void  enc1_nonrecyleCount(int cardNum){
	enc1_cmr=(COUNT_MODE_MASK & enc1_cmr) | ENC_ONE_CHANNEL | ENC_CMR_REGISTER | ENC_CMR_NONRECYCLE;
	iowrite8(enc1_cmr, &(q8Con->Q8reg->encoderControl.one.enc1));
}

void  enc2_nonrecyleCount(int cardNum){
	enc2_cmr=(COUNT_MODE_MASK & enc2_cmr) | ENC_ONE_CHANNEL | ENC_CMR_REGISTER | ENC_CMR_NONRECYCLE;
	iowrite8(enc2_cmr, &(q8Con->Q8reg->encoderControl.one.enc2));
}

void  enc3_nonrecyleCount(int cardNum){
	enc3_cmr=(COUNT_MODE_MASK & enc3_cmr) | ENC_ONE_CHANNEL | ENC_CMR_REGISTER | ENC_CMR_NONRECYCLE;
	iowrite8(enc3_cmr, &(q8Con->Q8reg->encoderControl.one.enc3));
}

void  enc4_nonrecyleCount(int cardNum){
	enc4_cmr=(COUNT_MODE_MASK & enc4_cmr) | ENC_ONE_CHANNEL | ENC_CMR_REGISTER | ENC_CMR_NONRECYCLE;
	iowrite8(enc4_cmr, &(q8Con->Q8reg->encoderControl.one.enc4));
}

void  enc5_nonrecyleCount(int cardNum){
	enc5_cmr=(COUNT_MODE_MASK & enc5_cmr) | ENC_ONE_CHANNEL | ENC_CMR_REGISTER | ENC_CMR_NONRECYCLE;
	iowrite8(enc5_cmr, &(q8Con->Q8reg->encoderControl.one.enc5));
}

void  enc6_nonrecyleCount(int cardNum){
	enc6_cmr=(COUNT_MODE_MASK & enc6_cmr) | ENC_ONE_CHANNEL | ENC_CMR_REGISTER | ENC_CMR_NONRECYCLE;
	iowrite8(enc6_cmr, &(q8Con->Q8reg->encoderControl.one.enc6));
}

void  enc7_nonrecyleCount(int cardNum){
	enc7_cmr=(COUNT_MODE_MASK & enc7_cmr) | ENC_ONE_CHANNEL | ENC_CMR_REGISTER | ENC_CMR_NONRECYCLE;
	iowrite8(enc7_cmr, &(q8Con->Q8reg->encoderControl.one.enc7));
}

///========================== FUNCTION HEADERS OF encX_moduloCount FUNCTIONS========================================
/// Name        : encX_moduloCount 
/// Input       : cardNum - PCI memory region that is mapped to Q8 card memory 
/// Output      : None
/// Return      : None
/// Description : Configures  the encoder channel of which number is specified by "X" as modulo count
///                                
///=====================================================================================================================
void enc0_moduloCount(int cardNum){
	enc0_cmr=(COUNT_MODE_MASK & enc0_cmr) | ENC_ONE_CHANNEL | ENC_CMR_REGISTER | ENC_CMR_MODULO;
	iowrite8(enc0_cmr, &(q8Con->Q8reg->encoderControl.one.enc0));
}

void   enc1_moduloCount(int cardNum){
	enc1_cmr=(COUNT_MODE_MASK & enc1_cmr) | ENC_ONE_CHANNEL | ENC_CMR_REGISTER | ENC_CMR_MODULO;
	iowrite8(enc1_cmr, &(q8Con->Q8reg->encoderControl.one.enc1));
}

void   enc2_moduloCount(int cardNum){
	enc2_cmr=(COUNT_MODE_MASK & enc2_cmr) | ENC_ONE_CHANNEL | ENC_CMR_REGISTER | ENC_CMR_MODULO;
	iowrite8(enc2_cmr, &(q8Con->Q8reg->encoderControl.one.enc2));
}

void   enc3_moduloCount(int cardNum){
	enc3_cmr=(COUNT_MODE_MASK & enc3_cmr) | ENC_ONE_CHANNEL | ENC_CMR_REGISTER | ENC_CMR_MODULO;
	iowrite8(enc3_cmr, &(q8Con->Q8reg->encoderControl.one.enc3));
}

void   enc4_moduloCount(int cardNum){
	enc4_cmr=(COUNT_MODE_MASK & enc4_cmr) | ENC_ONE_CHANNEL | ENC_CMR_REGISTER | ENC_CMR_MODULO;
	iowrite8(enc4_cmr, &(q8Con->Q8reg->encoderControl.one.enc4));
}

void   enc5_moduloCount(int cardNum){
	enc5_cmr=(COUNT_MODE_MASK & enc5_cmr) | ENC_ONE_CHANNEL | ENC_CMR_REGISTER | ENC_CMR_MODULO;
	iowrite8(enc5_cmr, &(q8Con->Q8reg->encoderControl.one.enc5));
}

void   enc6_moduloCount(int cardNum){
	enc6_cmr=(COUNT_MODE_MASK & enc6_cmr) | ENC_ONE_CHANNEL | ENC_CMR_REGISTER | ENC_CMR_MODULO;
	iowrite8(enc6_cmr, &(q8Con->Q8reg->encoderControl.one.enc6));
}

void   enc7_moduloCount(int cardNum){
	enc7_cmr=(COUNT_MODE_MASK & enc7_cmr) | ENC_ONE_CHANNEL | ENC_CMR_REGISTER | ENC_CMR_MODULO;
	iowrite8(enc7_cmr, &(q8Con->Q8reg->encoderControl.one.enc7));
}

///========================== FUNCTION HEADERS OF D/A Configuration FUNCTIONS========================================

/// Name        : dacconfigX_unipolar/bipolar_5/10
/// Input       : cardNum - PCI memory region that is mapped to Q8 card memory 
/// Output      : None
/// Return      : None
/// Description : Configures  the D/A channel of which number is specified by "X" bipolar/unipolar and 5/10 volt
///                                
///=====================================================================================================================
void dacconfig0_unipolar_10(int cardNum){
	analogModecurrent=ioread16( &(q8Con->Q8reg->analogMode.four.dac03) );
	iowrite16( (analogModecurrent & DAC04_MASK) | DAC0_UNIPOLAR_10V,
                   &(q8Con->Q8reg->analogMode.four.dac03));//MODE 
    iowrite16(0x0000,&(q8Con->Q8reg->analogModeUpdate.four.dac03));
}

void dacconfig0_bipolar_5(int cardNum){
	analogModecurrent=ioread16( &(q8Con->Q8reg->analogMode.four.dac03) );
	iowrite16( (analogModecurrent & DAC04_MASK) | DAC0_BIPOLAR_5V,
              &(q8Con->Q8reg->analogMode.four.dac03));
    iowrite16(0x0000,&(q8Con->Q8reg->analogModeUpdate.four.dac03));
}

void dacconfig0_bipolar_10(int cardNum) {
	analogModecurrent=ioread16( &(q8Con->Q8reg->analogMode.four.dac03) );
	iowrite16((analogModecurrent & DAC04_MASK) | DAC0_BIPOLAR_10V,
	          &(q8Con->Q8reg->analogMode.four.dac03));//MODE 
	iowrite16(0x0000,&(q8Con->Q8reg->analogModeUpdate.four.dac03));
}

void dacconfig1_bipolar_10(int cardNum) {
	analogModecurrent=ioread16( &(q8Con->Q8reg->analogMode.four.dac03) );
	iowrite16((analogModecurrent & DAC15_MASK) | DAC1_BIPOLAR_10V,
					&(q8Con->Q8reg->analogMode.four.dac03));//MODE 
	iowrite16(0x0000,&(q8Con->Q8reg->analogModeUpdate.four.dac03));
}

void dacconfig1_bipolar_5(int cardNum){
	analogModecurrent=ioread16( &(q8Con->Q8reg->analogMode.four.dac03) );
	iowrite16((analogModecurrent & DAC15_MASK) | DAC1_BIPOLAR_5V,
			&(q8Con->Q8reg->analogMode.four.dac03));//MODE 
    iowrite16(0x0000,&(q8Con->Q8reg->analogModeUpdate.four.dac03));
}


void dacconfig1_unipolar_10(int cardNum){
	analogModecurrent=ioread16( &(q8Con->Q8reg->analogMode.four.dac03) );
	iowrite16((analogModecurrent & DAC15_MASK) | DAC1_UNIPOLAR_10V,
				&(q8Con->Q8reg->analogMode.four.dac03));//M
    iowrite16(0x0000,&(q8Con->Q8reg->analogModeUpdate.four.dac03));
}

void dacconfig2_unipolar_10(int cardNum){
	analogModecurrent=ioread16( &(q8Con->Q8reg->analogMode.four.dac03) );
	iowrite16((analogModecurrent & DAC26_MASK) | DAC2_UNIPOLAR_10V,
			&(q8Con->Q8reg->analogMode.four.dac03));//MODE 
	iowrite16(0x0000,&(q8Con->Q8reg->analogModeUpdate.four.dac03));
}

void dacconfig2_bipolar_10(int cardNum){
	analogModecurrent=ioread16( &(q8Con->Q8reg->analogMode.four.dac03) );
	iowrite16((analogModecurrent & DAC26_MASK)| DAC2_BIPOLAR_10V,
				&(q8Con->Q8reg->analogMode.four.dac03));//MODE 
    iowrite16(0x0000,&(q8Con->Q8reg->analogModeUpdate.four.dac03));
}

void dacconfig2_bipolar_5(int cardNum){
	analogModecurrent=ioread16( &(q8Con->Q8reg->analogMode.four.dac03) );
	iowrite16((analogModecurrent & DAC26_MASK) | DAC2_BIPOLAR_5V,
				&(q8Con->Q8reg->analogMode.four.dac03));//MODE 
    iowrite16(0x0000,&(q8Con->Q8reg->analogModeUpdate.four.dac03));
}

void dacconfig3_bipolar_5(int cardNum){ 
	analogModecurrent=ioread16( &(q8Con->Q8reg->analogMode.four.dac03) );
	iowrite16((analogModecurrent & DAC37_MASK)| DAC3_BIPOLAR_5V,
				&(q8Con->Q8reg->analogMode.four.dac03));//MODE 
    iowrite16(0x0000,&(q8Con->Q8reg->analogModeUpdate.four.dac03));
}

void dacconfig3_bipolar_10(int cardNum) {
	analogModecurrent=ioread16( &(q8Con->Q8reg->analogMode.four.dac03) );
	iowrite16((analogModecurrent & DAC37_MASK)| DAC3_BIPOLAR_10V,
			&(q8Con->Q8reg->analogMode.four.dac03));//MODE 
	iowrite16(0x0000,&(q8Con->Q8reg->analogModeUpdate.four.dac03));
}

void dacconfig3_unipolar_10(int cardNum){
	analogModecurrent=ioread16( &(q8Con->Q8reg->analogMode.four.dac03) );
	iowrite16((analogModecurrent & DAC37_MASK) | DAC3_UNIPOLAR_10V,
				&(q8Con->Q8reg->analogMode.four.dac03));//MODE 
	iowrite16(0x0000,&(q8Con->Q8reg->analogModeUpdate.four.dac03));
}

void dacconfig4_unipolar_10(int cardNum){
	analogModecurrent=ioread16( &(q8Con->Q8reg->analogMode.four.dac47) );
	iowrite16((analogModecurrent & DAC04_MASK) | DAC4_UNIPOLAR_10V,
			&(q8Con->Q8reg->analogMode.four.dac47));//MODE 
	iowrite16(0x0000,&(q8Con->Q8reg->analogModeUpdate.four.dac47));
}

void dacconfig4_bipolar_10(int cardNum){
	analogModecurrent=ioread16( &(q8Con->Q8reg->analogMode.four.dac47) );
	iowrite16((analogModecurrent & DAC04_MASK) | DAC4_BIPOLAR_10V,
				&(q8Con->Q8reg->analogMode.four.dac47));//MODE 
	iowrite16(0x0000,&(q8Con->Q8reg->analogModeUpdate.four.dac47));
}

void dacconfig4_bipolar_5(int cardNum){
	analogModecurrent=ioread16( &(q8Con->Q8reg->analogMode.four.dac47) );
	iowrite16((analogModecurrent & DAC04_MASK) | DAC4_BIPOLAR_5V,
				&(q8Con->Q8reg->analogMode.four.dac47));//MODE 
    iowrite16(0x0000,&(q8Con->Q8reg->analogModeUpdate.four.dac47));
}

void dacconfig5_bipolar_5(int cardNum){ 
	analogModecurrent=ioread16( &(q8Con->Q8reg->analogMode.four.dac47) );
	iowrite16((analogModecurrent & DAC15_MASK) | DAC5_BIPOLAR_5V,
				&(q8Con->Q8reg->analogMode.four.dac47));//MODE 
	iowrite16(0x0000,&(q8Con->Q8reg->analogModeUpdate.four.dac47));
}

void dacconfig5_bipolar_10(int cardNum){
	analogModecurrent=ioread16( &(q8Con->Q8reg->analogMode.four.dac47) );
	iowrite16((analogModecurrent & DAC15_MASK) | DAC5_BIPOLAR_10V,
				&(q8Con->Q8reg->analogMode.four.dac47));//MODE 
    iowrite16(0x0000,&(q8Con->Q8reg->analogModeUpdate.four.dac47));
}

void dacconfig5_unipolar_10(int cardNum){
	analogModecurrent=ioread16( &(q8Con->Q8reg->analogMode.four.dac47) );
	iowrite16((analogModecurrent & DAC15_MASK) | DAC5_UNIPOLAR_10V,
				&(q8Con->Q8reg->analogMode.four.dac47));//MODE 
    iowrite16(0x0000,&(q8Con->Q8reg->analogModeUpdate.four.dac47));
}

void dacconfig6_unipolar_10(int cardNum){
	analogModecurrent=ioread16( &(q8Con->Q8reg->analogMode.four.dac47) );
	iowrite16((analogModecurrent & DAC26_MASK) | DAC6_UNIPOLAR_10V,
				&(q8Con->Q8reg->analogMode.four.dac47));//MODE 
	iowrite16(0x0000,&(q8Con->Q8reg->analogModeUpdate.four.dac47));
}

void dacconfig6_bipolar_10(int cardNum) {
	analogModecurrent=ioread16( &(q8Con->Q8reg->analogMode.four.dac47) );
	iowrite16((analogModecurrent & DAC26_MASK) | DAC6_BIPOLAR_10V,
				&(q8Con->Q8reg->analogMode.four.dac47));//MODE 
    iowrite16(0x0000,&(q8Con->Q8reg->analogModeUpdate.four.dac47));
}

void dacconfig6_bipolar_5(int cardNum)  {
	analogModecurrent=ioread16( &(q8Con->Q8reg->analogMode.four.dac47) );
	iowrite16((analogModecurrent & DAC26_MASK) | DAC6_BIPOLAR_5V,
				&(q8Con->Q8reg->analogMode.four.dac47));//MODE 
    iowrite16(0x0000,&(q8Con->Q8reg->analogModeUpdate.four.dac47));
}

void dacconfig7_bipolar_5(int cardNum)  {
	analogModecurrent=ioread16( &(q8Con->Q8reg->analogMode.four.dac47) );
	iowrite16((analogModecurrent & DAC37_MASK) | DAC7_BIPOLAR_5V,
				&(q8Con->Q8reg->analogMode.four.dac47));//MODE 
	iowrite16(0x0000,&(q8Con->Q8reg->analogModeUpdate.four.dac47));
}

void dacconfig7_bipolar_10(int cardNum) {
	analogModecurrent=ioread16( &(q8Con->Q8reg->analogMode.four.dac47) );
	iowrite16((analogModecurrent & DAC37_MASK) | DAC7_BIPOLAR_10V,
			&(q8Con->Q8reg->analogMode.four.dac47));//MODE 
    iowrite16(0x0000,&(q8Con->Q8reg->analogModeUpdate.four.dac47));
}

void dacconfig7_unipolar_10(int cardNum) {
	analogModecurrent=ioread16( &(q8Con->Q8reg->analogMode.four.dac47) );
	iowrite16((analogModecurrent & DAC37_MASK) | DAC7_UNIPOLAR_10V,
			&(q8Con->Q8reg->analogMode.four.dac47));//MODE 
			iowrite16(0x0000,&(q8Con->Q8reg->analogModeUpdate.four.dac47));
}

#endif
