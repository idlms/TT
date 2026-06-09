//--------------------------------------------------
// Text Table
//--------------------------------------------------

BYTE code tOSD_CHARWIDTH_ENGLISH2[][2] =
{
	{_,    12},

	{_0_, 12}, {_1_, 12}, {_2_, 12}, {_3_, 12}, {_4_, 12}, {_5_, 12}, {_6_, 12}, {_7_, 12}, {_8_, 12}, {_9_, 12},

	{_A_, 12}, {_B_,  12}, {_C_, 12}, {_D_,  12}, {_E_,  12}, {_F_,  12}, {_G_, 12}, {_H_,  12}, {_I_,  12}, {_J_,  12},
	{_K_, 12}, {_L_,  12}, {_M_, 12}, {_N_,  12}, {_O_, 12}, {_P_,  12}, {_Q_, 12}, {_R_, 12}, {_S_,  12}, {_T_,  12},
	{_U_,  12}, {_V_, 12}, {_W_, 12}, {_X_, 12}, {_Y_,  12}, {_Z_,  12}, {_DOT_,12},{_COLON_,12},{_PLUS_,12},{_AND_,12},
	{_LEFT_ARROWS_,12},{_RIGHT_ARROWS_,12},{_CH_JIAN,12},{_CH_TI,12},{_CH_ZHONG,12},{_CH_WEN,12},
	{_EU_C,12},{_EU_N,12},{_EU_E,12},{_EU_y,12},{_EU_c,12},{_EU_k,12},
	{_EU_n,12},{_EU_n1,12},{_KO_0,12},{_KO_1,12},
	_END_,
};

 BYTE code tOSD_CHARWIDTH_EUROPE[][2] =
 {
	 {_,	4},
 
	 //{_0_, 10}, {_1_, 8}, {_2_, 10}, {_3_, 10}, {_4_, 10}, {_5_, 10}, {_6_, 10}, {_7_, 10}, {_8_, 10}, {_9_, 10},
	 {_0_, 10}, {_1_, 10}, {_2_, 12}, {_3_, 12}, {_4_, 12}, {_5_, 12}, {_6_, 12}, {_7_, 12}, {_8_, 12}, {_9_, 12},
	 {_A_, 12}, {_B_,  12}, {_C_, 12}, {_D_,  12}, {_E_,  12}, {_F_,  10}, {_G_, 12}, {_H_,  12}, {_I_,  9}, {_J_,  10},
	 {_K_, 12}, {_L_,  11}, {_M_, 12}, {_N_,  11}, {_O_, 12}, {_P_,	12}, {_Q_, 12}, {_R_, 12}, {_S_,  11}, {_T_,  12},
	 {_U_,	12}, {_V_, 12}, {_W_, 12}, {_X_, 12}, {_Y_,  11}, {_Z_,  11},
 
 
	 {_a_,	9}, {_b_,  9}, {_c_,  9}, {_d_,  9}, {_e_,	9}, {_f_,  7}, {_g_,  9}, {_h_,  9}, {_i_,	3}, {_j_,  5},
 
	 {_k_,	8}, {_l_,  3}, {_m_, 12}, {_n_,  9}, {_o_,	9}, {_p_,  9}, {_q_,  9}, {_r_,  7}, {_s_,	8}, {_t_,  7},
	 {_u_,	9}, {_v_,  9}, {_w_, 12}, {_x_,  10}, {_y_,	10}, {_z_,  9},
	 
	 {_A0_,12}, {_A1_, 12}, {_A2_,12}, {_a2_, 9}, {_a3_, 9}, {_a4_, 12}, {_c0_, 9}, {_E0_, 12}, {_e0_, 12}, {_e1_, 12}, {_e2_, 9}, {_N0_, 9},
	 {_U0_, 9}, {_u1_, 12}, {_u2_, 12}, {_o0_, 12}, {_o1_, 12}, {_o2_, 12}, {_O3_, 12}, {_I0_, 4},
	 
	 {_DOWNDOT_, 12}, {_DOT_,	12}, {_LEFT_BRACE_, 12}, {_RIGHT_BRACE_, 12}, {_AND_,	  12}, {_COLON_,	   12}, {_AT_0_,		12},
	 {_COMMA_, 12}, {_SLINE_, 12}, {_SHIFT_LEFT_, 12}, {_SHIFT_RIGHT_, 12}, {_SEPERATE_, 12}, {_QUERY_, 	  12},
	 
	 _END_,
 };
	 
 BYTE code tOSD_CHARWIDTH_CHINESE[][2] =
 {
	 {_,	12},
	 
	 {_0_, 12}, {_1_, 12}, {_2_, 12}, {_3_, 12}, {_4_, 12}, {_5_, 12}, {_6_, 12}, {_7_, 12}, {_8_, 12}, {_9_, 12},
	 
	 {_A_, 12}, {_B_,  12}, {_C_, 12}, {_D_,  12}, {_E_,  12}, {_F_,  12}, {_G_, 12}, {_H_,  12}, {_I_,  12}, {_J_,  12},
	 {_K_, 12}, {_L_,  12}, {_M_, 12}, {_N_,  12}, {_O_, 12}, {_P_,  12}, {_Q_, 12}, {_R_, 12}, {_S_,  12}, {_T_,  12},
	 {_U_,	12}, {_V_, 12}, {_W_, 12}, {_X_, 12}, {_Y_,  12}, {_Z_,  12},
	 
	 
	 {_a_,	12}, {_b_, 12}, {_c_,  12}, {_d_, 12}, {_e_,  12}, {_f_,  12}, {_g_, 12}, {_h_,  12}, {_i_,  12}, {_j_,  12},
	 
	 {_k_, 12}, {_l_,  12}, {_m_, 12}, {_n_,  12}, {_o_,  12}, {_p_,  12}, {_q_,  12}, {_r_,  12}, {_s_,  12}, {_t_,  12},
	{_u_,  12}, {_v_,  12}, {_w_, 12}, {_x_, 12}, {_y_,  12}, {_z_, 12},
	 
	 {_A0_,12}, {_A1_, 12}, {_A2_, 12}, {_a2_, 12}, {_a3_,12}, {_a4_, 12}, {_c0_, 12}, {_E0_, 12}, {_e0_, 12}, {_e1_, 12}, {_e2_, 12}, {_N0_, 12},
	 {_U0_, 12}, {_u1_, 12}, {_u2_, 12}, {_o0_, 12}, {_o1_, 12}, {_o2_, 12}, {_O3_, 12}, {_I0_, 12},
	 
	 {_DOWNDOT_, 12}, {_DOT_,  12}, {_LEFT_BRACE_, 12}, {_RIGHT_BRACE_, 12}, {_AND_,	 12}, {_COLON_, 	  12}, {_AT_0_, 	   12},
	 {_COMMA_, 12}, {_SLINE_, 12}, {_SHIFT_LEFT_, 12}, {_SHIFT_RIGHT_, 12}, {_SEPERATE_, 12}, {_QUERY_, 	  12},
	 {_60_, 12}, {_61_, 12}, {_62_, 12}, {_63_, 12}, {_64_, 12}, {_65_, 12}, {_66_, 12}, {_67_, 12}, {_68_, 12}, {_69_, 12}, {_6a_, 12}, {_6b_, 12}, {_6c_, 12}, {_6d_, 12},  
	{_6e_, 12}, {_6f_, 12}, {_70_, 12}, {_71_, 12}, {_72_, 12}, {_73_, 12}, {_74_, 12}, {_75_, 12}, {_76_, 12}, {_77_, 12}, {_78_, 12}, {_79_, 12}, {_7a_, 12}, {_7b_, 12}, 
	 {_7c_, 12},{_7d_, 12},{_7e_, 12},{_7f_, 12},{_80_, 12},{_81_, 12},{_82_, 12},{_83_, 12},{_84_, 12},{_85_, 12},{_86_, 12},{_87_, 12},{_88_, 12},{_89_, 12},{_8a_, 12},
	 {_8b_, 12},{_8c_, 12},{_8d_, 12},{_8e_, 12},{_8f_, 12},{_90_, 12},{_91_, 12},{_92_, 12},{_93_, 12},{_94_, 12},{_95_, 12} ,{_96_, 12} ,{_97_, 12} ,{_98_, 12} ,{_99_, 12},
	 {_9a_, 12},{_9b_, 12},{_9c_, 12},{_9d_, 12}, {_9e_, 12}, {_9f_, 12},{_a0, 12},{_a1, 12},{_a2, 12},{_a3, 12},{_a4, 12},{_a5, 12},_END_,
 };  
#if 0
  BYTE code tSTRING_SHIFT_LEFT[] =
 {
	 _SHIFT_LEFT_,_END_,
 };
 
 BYTE code	tSTRING_SHIFT_RIGHT[] =
 {
	 _SHIFT_RIGHT_,_END_,
 };
#endif
  BYTE code tSTRING_ON[] =
 {
	 //_O_, _n_,_END_,
	 //_M_,_A_,_R_,_DOWNDOT_,_END_,
	 // _E_,_I_,_N_,_END_,
	 // _A_,_C_,_T_,_DOWNDOT_,_END_, 
	 //_O_, _N_,_END_,
	 //_A_,_A_,_N_,_END_,  
	 //0x0e,0x00,0x7c,_END_,
	 //0x65,0x00,0x66,_END_,
	 //0x65,0x00,0x66,_END_,
	  _O_,_n_,_END_,
	  _S_,_i_,_END_,
	  _M_,_a_,_r_,_c_,_h_,_e_,_END_,
	  _E_,_i_,_n_,_END_,
	  _O_,_n_,_END_,
	  _A_,_a_,_n_,_END_,
	   _B_,_EU_0x64,_EU_0x45,0x25,_END_, //Russia
	  0x92,0x00,0x57,_END_,
	  0x5b,0x00,0x7b,_END_,//
 };
 
 BYTE code	tSTRING_OFF[] =
 {
	// _O_, _f_,_f_,_END_,
	// _A_, _R_, _R_, _DOWNDOT_,_END_,
	//_A_, _U_, _S_, _END_,
	//_D_,_E_,_S_,_A_,_C_,_T_,_DOWNDOT_,_END_,
	// _O_, _F_,_F_,_END_,
	// _U_,_I_,_T_,_END_,
	//  0x5a,0x00,0x49,_END_,  
	// 0x63,0x00,0x64,_END_,
	// 0x63,0x00,0x64,_END_,
		  _O_,_f_,_f_,_END_,
	  _N_,_o_,_END_,
	  _A_,_r_,_r_,_e_,_t_,_END_,
	  _A_,_u_,_s_,_END_,
	  _O_,_f_,_f_,_END_,
	  _U_,_i_,_t_,_END_,
	  _B_,_EU_0x3B,_EU_0x64,_EU_0x45,0x25,_END_, //Russia
	  0x69,0x00,0x57,_END_,
	  0x40,0x00,0x7c,_END_,//
 };
 
 
 
#if 0
 BYTE code	tSTRING_COLOR_TEMP_9300[] =
 {
	 _9_,_3_,_0_,_0_, _END_,
	 _9_,_3_,_0_,_0_, _END_,
	 _9_,_3_,_0_,_0_, _END_,
	 _9_,_3_,_0_,_0_, _END_,
	 _9_,_3_,_0_,_0_, _END_,
	 _9_,_3_,_0_,_0_, _END_,
	 _9_,_3_,_0_,_0_, _END_,
	 _9_,_3_,_0_,_0_, _END_,
	 _9_,_3_,_0_,_0_, _END_,
 };
 
 BYTE code	tSTRING_COLOR_TEMP_6500[] =
 {
	 _6_, _5_,_0_,_0_,_END_,
	 _6_, _5_,_0_,_0_,_END_,
	 _6_, _5_,_0_,_0_,_END_,
	 _6_, _5_,_0_,_0_,_END_,
	 _6_, _5_,_0_,_0_,_END_,
	 _6_, _5_,_0_,_0_,_END_,
	 _6_, _5_,_0_,_0_,_END_,
	 _6_, _5_,_0_,_0_,_END_,
	 _6_, _5_,_0_,_0_,_END_,
 };
 
 BYTE code	tSTRING_COLOR_TEMP_5800[] =
 {
	 _5_, _8_,_0_,_0_,_END_,
	 _5_, _8_,_0_,_0_,_END_,
	 _5_, _8_,_0_,_0_,_END_,
	 _5_, _8_,_0_,_0_,_END_,
	 _5_, _8_,_0_,_0_,_END_,
	 _5_, _8_,_0_,_0_,_END_,
	 _5_, _8_,_0_,_0_,_END_,
	 _5_, _8_,_0_,_0_,_END_,
	 _5_, _8_,_0_,_0_,_END_,
 };
 
 BYTE code	tSTRING_COLOR_TEMP_sRGB[] =
 {
	 _S_, _R_,_G_,_B_,_END_,
	 _S_, _R_,_G_,_B_,_END_,
	 _S_, _R_,_G_,_B_,_END_,
	 _S_, _R_,_G_,_B_,_END_,
	 _S_, _R_,_G_,_B_,_END_,
	 _S_, _R_,_G_,_B_,_END_,
	 0x67,0x6b,0x6c,0x6d,_END_,
	 0x72,0x73,0x74,0x75,_END_,
	 _S_, _R_,_G_,_B_,_END_,
 };
 
 BYTE code	tSTRING_COLOR_TEMP_User[] =
 {
	 _U_, _S_,_E_,_R_,_END_,
	_U_, _T_, _I_, _L_, _I_, _S_, _DOWNDOT_,_END_,
	_B_, _E_, _N_, _U_, _T_, _Z_, _E_, _R_, _END_,
	_U_,_S_,_U_,_A_,_R_,_I_,_O_,_END_,
	_U_,_T_,_E_,_N_,_T_,_E_,_END_,
	_G_,_E_,_B_,_R_,_U_,_I_,_K_,_E_,_R_,_END_,
	0x50,0x00,0x51,0x00,0x1c,_END_,
	 0x56,0x00,0x57,_END_,
	 0x3e,0x00,0x3f,_END_,//
 };

 
 BYTE code	tSTRING_Color_Effect_Standard[] =
 {
	 _S_, _T_, _A_, _N_, _D_, _A_, _R_, _D_, _END_,
	 _S_, _T_, _A_, _N_, _D_, _A_, _R_, _D_, _END_,
	 _S_, _T_, _A_, _N_, _D_, _A_, _R_, _D_, _END_,
	 _E_,_S_,_T_,_A1_,_N_,_D_,_A_,_R_,_END_,
	 _S_,_T_,_A_,_N_,_D_,_A_,_R_,_D_,_END_,
	 _S_,_T_,_A_,_N_,_D_,_A_,_A_,_R_,_D_,_END_,
	  0x52,0x00,0x53,_END_,
	  0x5a,0x00,0x5b,_END_,
	  0x5a,0x00,0x5b,_END_,
 };
 
 BYTE code	tSTRING_Color_Effect_Movie[] =
 {
	 _M_, _O_, _V_, _I_, _E_, _END_,
	 _F_, _I_, _L_, _M_, _END_,
	 _F_, _I_, _L_, _M_, _END_,
	 _P_,_E_,_L_,_I0_,_C_,_U_,_L_,_A_,_END_,
	 _F_,_I_,_L_,_M_,_END_,
	 _F_,_I_,_L_,_M_,_END_,
	 0x55,0x00,0x2f,_END_,
	 0x5e,0x00,0x5f,_END_,
	 0x5e,0x00,0x5f,_END_,
 };
 
 BYTE code	tSTRING_Color_Effect_Game[] =
 {
	 _G_, _A_, _M_, _E_,_END_,
	  _J_, _E_, _U_, _END_, 
	 _S_, _P_, _I_, _E_, _L_,_END_, 
	_J_,_U_,_E_,_G_,_O_,_END_,
	  _G_,_I_,_O_,_C_,_H_,_I_,_END_,
	  _S_,_P_,_E_,_L_,_END_,
	 0x56,0x00,0x57,_END_,
	 0x60,0x00,0x61,_END_, 
	 0x60,0x00,0x61,_END_, 
 };
 
 BYTE code	tSTRING_Color_Effect_Photo[] =
 {
	 _P_, _H_, _O_, _T_, _O_,_END_,
	 _P_, _H_, _O_, _T_, _O_,_END_,
	 _F_, _O_, _T_, _O_,_END_,
	 _F_,_O_,_T_,_O_,_END_,
	 _F_,_O_,_T_,_O_,_END_,
	 _F_,_O_,_T_,_O_,_END_,
	 0x50,0x00,0x11,_END_,
	 0x0b,0x00,0x62,_END_,
	 0x0b,0x00,0x62,_END_,	 
 };
 /*
#if(_USER_FUNCTION_FPS1_FPS2==_ON)
     #if((_LOGO_TYPE == _SANC_LOGO) || (_LOGO_TYPE == _SANC_SECPTRE_LOGO))
	  BYTE code tSTRING_Color_Effect_FPS1[] =
	  {
		  _F_,_P_,_S_,_END_,
		  _F_,_P_,_S_,_END_,
		  _F_,_P_,_S_,_END_,
		  _F_,_P_,_S_,_END_,
		  _F_,_P_,_S_,_END_,
		  _F_,_P_,_S_,_END_,
		  0x70,0x6a,0x67,_END_,
		  0x76,0x71,0x72,_END_,
		  0x76,0x71,0x72,_END_,
	  };
	  BYTE code tSTRING_Color_Effect_FPS2[] =
	  {
		  _R_,_T_,_S_,_END_,
		  _R_,_T_,_S_,_END_,
		  _R_,_T_,_S_,_END_,
			_R_,_T_,_S_,_END_,
		  _R_,_T_,_S_,_END_,
		  _R_,_T_,_S_,_END_,
 
		  0x6b,0x84,0x67,_END_,
		  0x73,0x7f,0x72,_END_,
		  0x73,0x7f,0x72,_END_,
	  };
     #else
 
		 BYTE code tSTRING_Color_Effect_FPS1[] =
		 {
			 _F_,_P_,_S_,_1_,_END_,
			 _F_,_P_,_S_,_1_,_END_,
			 _F_,_P_,_S_,_1_,_END_,
			 _F_,_P_,_S_,_1_,_END_,
			 _F_,_P_,_S_,_1_,_END_,
			 _F_,_P_,_S_,_1_,_END_,
			 0x70,0x6a,0x67,_1_,_END_,
			 0x76,0x71,0x72,_1_,_END_,
			 0x76,0x71,0x72,_1_,_END_,
		 };
		 BYTE code tSTRING_Color_Effect_FPS2[] =
		 {
			 _F_,_P_,_S_,_2_,_END_,
			 _F_,_P_,_S_,_2_,_END_,
			 _F_,_P_,_S_,_2_,_END_,
			 _F_,_P_,_S_,_2_,_END_,
			 _F_,_P_,_S_,_2_,_END_,
			 _F_,_P_,_S_,_2_,_END_,
			 0x70,0x6a,0x67,_2_,_END_,
			 0x76,0x71,0x72,_2_,_END_,
			 0x76,0x71,0x72,_2_,_END_,
		 };
		 
  #endif
		 
#endif   
 
 */
#endif
 BYTE code	tSTRING_Gamma_18[] =
 {
	 _1_,_DOT_,_8_,_END_,
	 _1_,_DOT_,_8_,_END_,
	 _1_,_DOT_,_8_,_END_,
	 _1_,_DOT_,_8_,_END_,
	 _1_,_DOT_,_8_,_END_,
	 _1_,_DOT_,_8_,_END_,
	 _1_,0x25,_8_,_END_,
	 _1_,0x25,_8_,_END_,
	 _1_,0x25,_8_,_END_,//
 };
 
 BYTE code	tSTRING_Gamma_20[] =
 {
	 _2_,_DOT_,_0_,_END_,
	 _2_,_DOT_,_0_,_END_,
	 _2_,_DOT_,_0_,_END_,
	 _2_,_DOT_,_0_,_END_,
	 _2_,_DOT_,_0_,_END_,
	 _2_,_DOT_,_0_,_END_,
	 _2_,0x25,_0_,_END_,
	 _2_,0x25,_0_,_END_,
	 _2_,0x25,_0_,_END_,//
 
 };
 
 BYTE code	tSTRING_Gamma_22[] =
 {
	 _2_,_DOT_,_2_,_END_,
	 _2_,_DOT_,_2_,_END_,
	 _2_,_DOT_,_2_,_END_,
	 _2_,_DOT_,_2_,_END_,
	 _2_,_DOT_,_2_,_END_,
	 _2_,_DOT_,_2_,_END_,
	 _2_,0x25,_2_,_END_,
	 _2_,0x25,_2_,_END_,
	 _2_,0x25,_2_,_END_,//
 };
 
 BYTE code	tSTRING_Gamma_24[] =
 {
	 _2_,_DOT_,_4_,_END_,
	 _2_,_DOT_,_4_,_END_,
	 _2_,_DOT_,_4_,_END_,
	 _2_,_DOT_,_4_,_END_,
	 _2_,_DOT_,_4_,_END_,
	 _2_,_DOT_,_4_,_END_,
	 _2_,0x25,_4_,_END_,
	 _2_,0x25,_4_,_END_,
	 _2_,0x25,_4_,_END_,//
 
 };
#if(_TECNINT_DICOM)
 BYTE code	tSTRING_Gamma_RC2[] =
 {
	 _D_,_I_,_C_,_O_,_M_,_SLINE_,_R_,_C_,_2_,_END_,
	 _D_,_I_,_C_,_O_,_M_,_SLINE_,_R_,_C_,_2_,_END_,
	 _D_,_I_,_C_,_O_,_M_,_SLINE_,_R_,_C_,_2_,_END_,
	 _D_,_I_,_C_,_O_,_M_,_SLINE_,_R_,_C_,_2_,_END_,
	 _D_,_I_,_C_,_O_,_M_,_SLINE_,_R_,_C_,_2_,_END_,
	 _D_,_I_,_C_,_O_,_M_,_SLINE_,_R_,_C_,_2_,_END_,
	 _D_,_I_,_C_,_O_,_M_,_SLINE_,_R_,_C_,_2_,_END_,
	 _D_,_I_,_C_,_O_,_M_,_SLINE_,_R_,_C_,_2_,_END_,
	 _D_,_I_,_C_,_O_,_M_,_SLINE_,_R_,_C_,_2_,_END_,//
 };
 
BYTE code	tSTRING_Gamma_RC3[] =
 {
		_D_,_I_,_C_,_O_,_M_,_SLINE_,_R_,_C_,_3_,_END_,
		_D_,_I_,_C_,_O_,_M_,_SLINE_,_R_,_C_,_3_,_END_,
		_D_,_I_,_C_,_O_,_M_,_SLINE_,_R_,_C_,_3_,_END_,
		_D_,_I_,_C_,_O_,_M_,_SLINE_,_R_,_C_,_3_,_END_,
		_D_,_I_,_C_,_O_,_M_,_SLINE_,_R_,_C_,_3_,_END_,
		_D_,_I_,_C_,_O_,_M_,_SLINE_,_R_,_C_,_3_,_END_,
		_D_,_I_,_C_,_O_,_M_,_SLINE_,_R_,_C_,_3_,_END_,
		_D_,_I_,_C_,_O_,_M_,_SLINE_,_R_,_C_,_3_,_END_,
		_D_,_I_,_C_,_O_,_M_,_SLINE_,_R_,_C_,_3_,_END_,//
 }; 
  #endif
 BYTE code tSTRING_0_Degree[] =
 {
	 _0_,_END_,
	 _0_,_END_,
	 _0_,_END_,
	 _0_,_END_,
	 _0_,_END_,
	 _0_,_END_,
	 _0_,_END_,
	 _0_,_END_,
	 _0_,_END_,//
 };

 BYTE code tSTRING_90_Degree[] =
 {
	 _9_,_0_,_END_,
	 _9_,_0_,_END_,
	 _9_,_0_,_END_,
	 _9_,_0_,_END_,
	 _9_,_0_,_END_,
	 _9_,_0_,_END_,
	 _9_,_0_,_END_,
	 _9_,_0_,_END_,
	 _9_,_0_,_END_,//
 };
 BYTE code tSTRING_180_Degree[] =
 {
	 _1_,_8_,_0_,_END_,
	 _1_,_8_,_0_,_END_,
	 _1_,_8_,_0_,_END_,
	 _1_,_8_,_0_,_END_,
	 _1_,_8_,_0_,_END_,
	 _1_,_8_,_0_,_END_,
	 _1_,_8_,_0_,_END_,
	 _1_,_8_,_0_,_END_,
	 _1_,_8_,_0_,_END_,//
 };
 BYTE code tSTRING_270_Degree[] =
 {
	 _2_,_7_,_0_,_END_,
	 _2_,_7_,_0_,_END_,
	 _2_,_7_,_0_,_END_,
	 _2_,_7_,_0_,_END_,
	 _2_,_7_,_0_,_END_,
	 _2_,_7_,_0_,_END_,
	 _2_,_7_,_0_,_END_,
	 _2_,_7_,_0_,_END_,
	 _2_,_7_,_0_,_END_,//
 };

 BYTE code	tSTRING_DP_Option_D011[] =
 {
  _1_,_DOT_,_1_,_END_, 
 };
 BYTE code	tSTRING_DP_Option_D012[] =
 {
   _1_,_DOT_,_2_,_END_,
 };
 BYTE code	tSTRING_Ultra_Vivid_L[] =
 {
	 _L_,_END_,
	_B_,_A_ ,_S_ ,_END_,
	_T_,_I_ ,_E_ ,_F_,_END_,
	 _L_,_END_,
	 _L_,_END_,
	 _L_,_END_,
	0x5e,0x00,0x53,_END_,
	 0x67,_END_,
	 0x67,_END_,
 };
 
 BYTE code	tSTRING_Ultra_Vivid_M[] =
 {
	 _M_,_END_,
	 _M_, _I_, _L_, _I_, _E_, _U_, _END_,
	 _M_, _I_, _T_, _T_, _E_,  _END_,
	 _M_,_END_,
	 _M_,_END_,
	 _M_,_END_,
	 0x60,0x00,0x46,_END_,
	0x34,_END_,
	0x34,_END_,
 };
 
 BYTE code	tSTRING_Ultra_Vivid_H[] =
 {
	 _H_,_END_,
	 _H_,_A_,_U_,_T_,_END_,
	 _H_,_O_,_C_,_H_,_END_,
	 _H_,_END_,
	 _H_,_END_,
	 _H_,_END_,
	 0x61,0x00,0x53,_END_,
	  0x68,_END_, 
	  0x68,_END_, 
 };
 
 BYTE code	tSTRING_Aspect_Ratio_full[] =
 {
	 _F_,_U_,_L_ ,_L_,_END_,
	 _P_, _L_, _E_, _I_, _N_,  _END_,
	 _V_, _O_, _L_, _L_, _END_,
	  _C_, _O_, _M_, _P_, _L_, _E_, _T_, _O_, _END_,
	  _C_, _O_, _M_, _P_, _L_, _E_, _T_, _O_, _END_,
	  _V_, _O_, _L_, _END_,
	  0x62,0x00,0x0d,0x00,0x33,_END_, //Russia
	  0x6a,0x00,0x6b,_END_,
	  0x6a,0x00,0x6b,_END_,
 };
 
 BYTE code	tSTRING_Aspect_Ratio_169[] =
 {
	 _1_, _6_,_COLON_,_9_,_END_,
	 _1_, _6_,_COLON_,_9_,_END_,
	 _1_, _6_,_COLON_,_9_,_END_,
	 _1_, _6_,_COLON_,_9_,_END_,
	 _1_, _6_,_COLON_,_9_,_END_,
	 _1_, _6_,_COLON_,_9_,_END_,
	 _1_, _6_, 0x26, _9_,_END_, //Russia
	 _1_, _6_,_COLON_,_9_,_END_,
	 _1_, _6_,_COLON_,_9_,_END_,
 
 };
 
 BYTE code	tSTRING_Aspect_Ratio_43[] =
 {
	 _4_,_COLON_,_3_,_END_,
	 _4_,_COLON_,_3_,_END_,
	 _4_,_COLON_,_3_,_END_,
	 _4_,_COLON_,_3_,_END_,
	 _4_,_COLON_,_3_,_END_,
	 _4_,_COLON_,_3_,_END_,
	 _4_,0x26,_3_,_END_, //Russia
	 _4_,_COLON_,_3_,_END_,
	 _4_,_COLON_,_3_,_END_,
 };
 
 
 BYTE code	tSTRING_Aspect_Ratio_54[] =
 {
	 _5_,_COLON_,_4_,_END_,
	 _5_,_COLON_,_4_,_END_,
	 _5_,_COLON_,_4_,_END_,
	 _5_,_COLON_,_4_,_END_,
	 _5_,_COLON_,_4_,_END_,
	 _5_,_COLON_,_4_,_END_,
	 _5_,0x26,_4_,_END_, //Russia
	 _5_,_COLON_,_4_,_END_,
	 _5_,_COLON_,_4_,_END_,
 };
 
 BYTE code	tSTRING_Aspect_Ratio_11[] =
 {
	 _1_,_COLON_,_1_,_END_,
	 _1_,_COLON_,_1_,_END_,
	 _1_,_COLON_,_1_,_END_,
	 _1_,_COLON_,_1_,_END_,
	 _1_,_COLON_,_1_,_END_,
	 _1_,_COLON_,_1_,_END_,
	  _1_,0x26,_1_,_END_, //Russia
	 _1_,_COLON_,_1_,_END_,
	 _1_,_COLON_,_1_,_END_,
 
 };
 /*
 BYTE code tSTRING_DP_EDID[] =
 {
	 _D_,_P_,_,_E_,_D_ ,_I_,_D_,_END_,
 };
 */
 /*
 BYTE code tSTRING_OD[] =
 {
	 _O_,_D_,_END_,
 };
 */
 BYTE code tSTRING_DP_EDID_1080P[] =
 {
	 _1_,_0_, _8_,_0_,_P_,_END_,
  };
 BYTE code tSTRING_DP_EDID_2560X1440[] =
 {
	 _2_,_5_, _6_,_0_,_X_,_1_,_4_, _4_,_0_,_END_,
 };
 BYTE code		 tSTRING_DP_EDID_4k2k30hz[] =
 {
	 _4_,_K_, _2_,_K_,_AT_0_,_3_,_0_,_H_,_z_,_END_,
 };
 BYTE code		 tSTRING_DP_EDID_4k2k60hz[] =
 {
	 _4_,_K_, _2_,_K_,_AT_0_,_6_,_0_,_H_,_z_,_END_,
 };
 
#if 0
 BYTE code	tSTRING_Audio_Source_Analog[] =
 {
	 _A_,_N_,_A_,_L_,_O_,_G_,_END_,
	_A_,_N_,_A_,_L_,_O_,_G_,_I_,_Q_,_U_,_E_,_END_,
	 _A_,_N_,_A_,_L_,_O_,_G_,_END_,
	 _A_, _N_, _A_, _L_, _O3_, _G_, _I_, _C_, _A_,_END_,
	 _A_, _N_, _A_, _L_, _O_, _G_, _I_, _C_, _O_, _END_,
	 _A_, _N_, _A_, _L_, _O_, _G_, _END_,
	 0x63,0x00,0x27,0x00,0x29,0x00,0x0b,_END_,
	 0x6c,0x00,0x6d,_END_,
	  0x6c,0x00,0x6d,_END_,
 };
 
 BYTE code	tSTRING_Audio_Source_Digital[] =
 {
	 _D_,_I_,_G_,_I_,_T_,_A_,_L_,_END_,
	 _D_,_I_,_G_,_I_,_T_,_A_,_L_,_END_,
	 _D_,_I_,_G_,_I_,_T_,_A_,_L_,_END_,
	 _D_,_I_,_G_,_I_,_T_,_A_,_L_,_END_,
	 _D_,_I_,_G_,_I_,_T_,_A_,_L_,_E_,_END_,
	 _D_,_I_,_G_,_I_,_T_,_A_,_A_,_L_,_END_,
	 0x15,0x00,0x39,0x00,0x64,_END_,
	  0x6e,0x00,0x6f,_END_,
	  0x6e,0x00,0x6f,_END_,
 };
 
 
 BYTE code	tSTRING_Audio_Source_Auto[] =
 {
	 _A_,_U_,_T_,_O_,_END_,
	 _A_,_U_,_T_,_O_,_END_,
	 _A_,_U_,_T_,_O_,_END_,
	 _A_,_U_,_T_,_O_,_M_,_A1_,_T_,_I_,_C_,_A_,_END_,
	 _A_,_U_,_T_,_O_,_M_,_A_,_T_,_I_,_C_,_A_,_END_,
	 _A_,_U_,_T_,_O_,_M_,_A_,_T_,_I_,_S_,_C_,_H_,_END_,
	 0x1c,0x00,0x1d,_END_,
		0x13,0x00,0x14,_END_,
		0x13,0x00,0x14,_END_,
 };
#endif

 BYTE code	tSTRING_LANGUAGE_ADJ[] =
 {
	 _E_,_N_,_G_,_L_,_I_,_S_,_H_,_END_, //Ӣ��
	  _F_,_R_,_A_,_N_,_c0_,_A_,_I_,_S_,_END_, // ����
	  _D_,_E_,_U_,_T_,_S_,_C_,_H_,_END_, // ����
	  _E_,_S_,_P_,_A_,_N0_,_A_,_END_,//��������
	  _I_,_T_,_A_,_L_,_I_,_A_,_N_,_O_,_END_,		  //�������
	  _N_,_E_,_D_,_E_,_R_,_L_,_A_,_N_,_D_,_END_,							 //������
	  _EU_0x70,_EU_0x3A,_EU_0x3B,_EU_0x64,_END_, //Russia
	  0x33,0x00,0x65,0x00,0x44,_END_, // ����
	  0x32,0x00,0x33,0x00,0x34,0x00,0x35,_END_, //��������
	 

 };
 
 BYTE code	 tSTRING_COLOR_TEMP_USER_R[] =
 {
	 _U_,_S_,_E_,_R_,_,_R_,_E_,_D_,_END_,
	 _R_,_O_,_U_,_G_,_E_,_END_, 
	 _R_,_O_,_T_,_END_,
	 _R_,_O_,_J_,_O_,_END_,
	 _R_,_O_,_S_,_S_,_O_,_END_,
	 _R_,_O_,_O_,_D_,_END_,
	 _EU_0x46,_EU_0x5F,_EU_0x61,_EU_0x60,_EU_0x53,_EU_0x3B,_EU_0x66,_END_, //Russia
	 0x4d,0x00,0x0f,_END_,
	 0x52,_END_,

 };
 
 BYTE code	 tSTRING_COLOR_TEMP_USER_G[] =
 {
	 _U_,_S_,_E_,_R_,_,_G_,_R_,_E_,_E_,_N_,_END_,
	  _V_,_E_,_R_,_T_,_END_,	
	 _G_,_R_,_u1_,_N_,_END_,
	 _V_,_E_,_R_,_D_,_E_,_END_,
	 _V_,_E_,_R_,_D_,_E_,_END_,
	 _G_,_R_,_O_,_E_,_N_,_E_,_END_,
	 _EU_0x54,_EU_0x62,_EU_0x45,_EU_0x60,_EU_0x53,_EU_0x3B,_EU_0x66,_END_, //Russia
	 0x4e,0x00,0x0f,_END_,
	  0x53,_END_,

 };
 
 BYTE code	 tSTRING_COLOR_TEMP_USER_B[] =
 {
	 _U_,_S_,_E_,_R_,_,_B_,_L_,_U_,_E_,_END_,
	_B_,_L_,_E_,_U_,_END_,	  
	_B_,_L_,_A_,_U_,_END_,	 
	_A_,_Z_,_U_,_L_,_END_,
	_B_,_L_,_U_,_END_,
	_B_,_L_,_A_,_U_,_W_,_E_,_END_,
	_C_,_EU_0x65,_EU_0x53,_EU_0x65,_EU_0x66,_END_, //Russia
    0x4f,0x00,0x0f,_END_, 
	0x55,_END_,

 };
 
 BYTE code	ONOFF_TABLE1[2] =
 {
	_STRING_OFF, _STRING_ON, 
 };
 
 
  BYTE code    _tCOLOR_TEMP[] =
  {
	   _C_,_o_,_l_,_o_,_r_,_,_T_,_e_,_m_,_p_,_END_,
	   _T_,_e_,_m_,_p_,_,_C_,_o_,_l_,_o_,_r_,_END_,
	   _T_,_e_,_m_,_p_,_,_d_,_e_,_,_c_,_o_,_u_,_l_,_e_,_u_,_r_,_END_,
	   _F_,_a_,_r_,_b_,_t_,_e_,_m_,_p_,_e_,_r_,_a_,_t_,_u_,_r_,_END_,
	   _T_,_e_,_m_,_p_,_DOT_,_c_,_o_,_l_,_o_,_r_,_e_,_END_,
	   _K_,_l_,_e_,_u_,_r_,_t_,_e_,_m_,_p_,_e_,_r_,_a_,_t_,_u_,_u_,_r_,_END_,
	   //_EU_0x41,0x43,0x62,0x39,0x5e,0x43,0x61,0x5d,0x00,0x39,0x62,0x5c,0x5a,0x62,0x5f,0x61,0x39,0x63,0x5f,0x61,_END_, // Russia (���Ӭ֬��ӬѬ� ��֬ެ�֬�Ѭ����)
	   _EU_0x41,0x43,0x62,0x27,0x5e,0x43,0x61,0x5d,0x27,0x62,0x5c,0x5A,0x25,_END_, // Russia (���Ӭ֬��ӬѬ� ��֬ެ�֬�Ѭ����) // 0x39
	   0x34,0x00,0x35,0x00,0x36,_END_, 
	   0x29,0x00,0x45,_END_, //

  };
   BYTE code _tSTRING_COLOR_RED[] =
   {
		_R_,_e_,_d_,_END_,
	   _R_,_o_,_j_,_o_,_END_,	 
		_R_,_o_,_u_,_g_,_e_,_END_,	  
		_R_,_o_,_t_,_END_,	  
		_R_,_o_,_s_,_s_,_o_,_END_,	  
		_R_,_o_,_o_,_d_,_END_,
		_EU_0x46,_EU_0x5F,_EU_0x61,_EU_0x60,_EU_0x53,_EU_0x3B,_EU_0x66,_END_,  //Russia
		0x37,0x00,0x38,_END_, 
		0x46,_END_,//

   };
   BYTE code _tSTRING_COLOR_GREEN[] =
   {
		_G_,_r_,_e_,_e_,_n_,_END_,
	   _V_,_e_,_r_,_d_,_e_,_END_,	 
		_V_,_e_,_r_,_t_,_END_,	  
	   _G_,_r_,_U0_,_n_,_END_,
		_V_,_e_,_r_,_d_,_e_,_END_,	  
		_G_,_r_,_o_,_e_,_n_,_e_,_END_,
		_EU_0x54,_EU_0x62,_EU_0x45,_EU_0x60,_EU_0x53,_EU_0x3B,_EU_0x66,_END_,//Russia
		0x39,0x00,0x3a,_END_, 
		0x47,_END_,//

   };
   BYTE code _tSTRING_COLOR_BLUE[] =
   {
		_B_,_l_,_u_,_e_,_END_,
	   _A_,_z_,_u_,_l_,_END_,	 
		_B_,_l_,_e_,_u_,_END_,
		_B_,_l_,_a_,_u_,_END_,
	   _B_,_l_,_u_,_END_,
		_B_,_l_,_a_,_u_,_w_,_e_,_END_,
		_C_,_EU_0x65,_EU_0x53,_EU_0x65,_EU_0x66,_END_,//Russia
		0x3b,0x00,0x3c,_END_, 
		0x48,_END_,//

   };
   BYTE code _tSTRING_COLOR_HDR[] =
   {
		_H_,_D_,_R_,_END_,
		_H_,_D_,_R_,_END_,	 
		_H_,_D_,_R_,_END_,
		_H_,_D_,_R_,_END_,
		_H_,_D_,_R_,_END_,
		_H_,_D_,_R_,_END_,
		_H_,_D_,_R_,_END_,
		_H_,_D_,_R_,_END_,
		_H_,_D_,_R_,_END_,//
   };   
   
   BYTE code _tSTRING_COLOR_6500K[] =
   {
	   _6_,_5_,_0_,_0_,_K_,_END_,
	   _6_,_5_,_0_,_0_,_K_,_END_,
	   _6_,_5_,_0_,_0_,_K_,_END_,
	   _6_,_5_,_0_,_0_,_K_,_END_,
	   _6_,_5_,_0_,_0_,_K_,_END_,
	   _6_,_5_,_0_,_0_,_K_,_END_,
	   _6_,_5_,_0_,_0_,_K_,_END_, //Russia
	   _6_,_5_,_0_,_0_,_K_,_END_,
	   _6_,_5_,_0_,_0_,_K_,_END_,//
   };
     BYTE code _tSTRING_COLOR_9300K[] =
   {
		_9_,_3_,_0_,_0_,_K_,_END_,
		_9_,_3_,_0_,_0_,_K_,_END_,
		_9_,_3_,_0_,_0_,_K_,_END_,
		_9_,_3_,_0_,_0_,_K_,_END_,
		_9_,_3_,_0_,_0_,_K_,_END_,
		_9_,_3_,_0_,_0_,_K_,_END_,
		_9_,_3_,_0_,_0_,_K_,_END_, //Russia
		_9_,_3_,_0_,_0_,_K_,_END_,
		_9_,_3_,_0_,_0_,_K_,_END_,//
   };
	 BYTE code _tSTRING_COLOR_7500K[] =
	 {
		  _7_,_5_,_0_,_0_,_K_,_END_,
		  _7_,_5_,_0_,_0_,_K_,_END_,
		  _7_,_5_,_0_,_0_,_K_,_END_,
		  _7_,_5_,_0_,_0_,_K_,_END_,
		  _7_,_5_,_0_,_0_,_K_,_END_,
		  _7_,_5_,_0_,_0_,_K_,_END_,
		  _7_,_5_,_0_,_0_,_K_,_END_, //Russia
		  _7_,_5_,_0_,_0_,_K_,_END_,
		  _7_,_5_,_0_,_0_,_K_,_END_,//
	 };
	 BYTE code _tSTRING_COLOR_5800K[] =
	 {
		  _5_,_8_,_0_,_0_,_K_,_END_,
		  _5_,_8_,_0_,_0_,_K_,_END_,
		  _5_,_8_,_0_,_0_,_K_,_END_,
		  _5_,_8_,_0_,_0_,_K_,_END_,
		  _5_,_8_,_0_,_0_,_K_,_END_,
		  _5_,_8_,_0_,_0_,_K_,_END_,
		  _5_,_8_,_0_,_0_,_K_,_END_, //Russia
		  _5_,_8_,_0_,_0_,_K_,_END_,
		  _5_,_8_,_0_,_0_,_K_,_END_,//
	 };

	 BYTE code _tSTRING_COLOR_SRGB[] =
	 {
		  _S_,_R_,_G_,_B_,_END_,
		  _S_,_R_,_G_,_B_,_END_,
		  _S_,_R_,_G_,_B_,_END_,
		  _S_,_R_,_G_,_B_,_END_,
		  _S_,_R_,_G_,_B_,_END_,
		  _S_,_R_,_G_,_B_,_END_,
		  _S_,_R_,_G_,_B_,_END_, //Russia
		  _S_,_R_,_G_,_B_,_END_,
		  _S_,_R_,_G_,_B_,_END_,//
	 };
	 BYTE code _tSTRING_COLOR_USER_DEFINE[] =
	 {
		  _U_,_s_,_e_,_r_,_,_D_,_e_,_f_,_i_,_n_,_e_,_END_,
		  _P_,_e_,_r_,_s_,_o_,_n_,_a_,_l_,_i_,_z_,_a_,_d_,_o_,_END_,
		  _D_,_e2_,_f_,_i_,_n_,_i_,_,_p_,_a_,_r_,_,_u_,_t_,_i_,_DOT_,_END_,
		  _B_,_e_,_n_,_u_,_t_,_z_,_e_,_r_,_d_,_e_,_f_,_i_,_n_,_i_,_DOT_,_END_,
		  _P_,_e_,_r_,_s_,_o_,_n_,_a_,_l_,_i_,_z_,_z_,_a_,_t_,_o_,_END_,
		  _G_,_e_,_b_,_r_,_u_,_i_,_k_,_e_,_r_,_END_,
		  _EU_0x44,_EU_0x5E,_EU_0x45,_EU_0x3C,_EU_0x3A,0x25,_END_, //Russia
		  0x64, 0x00,0x65,0x00, 0x66,0x00,0x67,0x00, 0x68,_END_,
		  0x66,0x00,0x75,0x00,0x7a,_END_,//
	 };

 BYTE code _tSTRING_COLOR_SMPTE2084[] =
 {
	  _O_,_n_,_END_,
	  _A_,_c_,_t_,_i_,_v_,_a_,_d_,_o_,_END_,	
	  _A_,_c_,_t_,_i_,_v_,_i_,_END_,	
	 _E_,_i_,_n_,_END_,
	  _A_,_t_,_t_,_v_,_a_,_t_,_o_,_END_,	
	  0x92,0x00,0x57,_END_,
	  0x5b,_END_, 
	 0x67,0x00,0x68,_END_,
		  0x67,0x00,0x68,_END_,
 };
 BYTE code _tSTRING_COLOR_OFF[] =
 {
	  _O_,_f_,_f_,_END_,
	  _N_,_o_,_END_,
	  _A_,_r_,_r_,_e_,_t_,_END_,
	  _A_,_u_,_s_,_END_,
	  _O_,_f_,_f_,_END_,
	  _U_,_i_,_t_,_END_,
	  _B_,_EU_0x3B,_EU_0x64,_EU_0x45,0x25,_END_, //Russia
	  0x69,0x00,0x57,_END_,
	  0x40,_END_,
 };
 BYTE code _tSTRING_COLOR_AUTO[] =
 {
	  _A_,_u_,_t_,_o_,_END_,
	  _a_,_u_,_t_,_o_,_m_,_a_,_t_,_i_,_c_,_o_,_END_,
	  _A_,_u_,_t_,_o_,_m_,_a_,_t_,_i_,_q_,_u_,_e_,_END_,
	  _A_,_u_,_t_,_o_,_m_,_a_,_t_,_i_,_s_,_c_,_h_,_e_,_END_,
	  _A_,_u_,_t_,_o_,_m_,_a_,_t_,_i_,_c_,_a_,_END_,
	  _A_,_U_,_T_,_O_,_END_,
	  0x0B, 0x43, 0x27, 0x5E, _END_, //Russia
	  0x66,0x00,0x80,0x00,0x53,0x00,0x55,_END_,
	  0x66,0x00,0x67,_END_,//
 };
///OTHER

 BYTE code _tSTRING_OTHER_DISPLAY_SIZE[] =
 {
	  _D_,_i_,_s_,_p_,_l_,_a_,_y_,_,_S_,_i_,_z_,_e_,_END_,
	  _A_,_s_,_p_,_e_,_c_,_t_,_o_,_END_,
	  _A_,_s_,_p_,_e_,_c_,_t_,_END_,
	  _A_,_s_,_p_,_e_,_k_,_t_,_END_,
	  _A_,_s_,_p_,_e_,_e_,_t_,_t_,_o_,_END_,
	  _A_,_s_,_p_,_e_,_c_,_t_,_END_,
	  _B_,_EU_0x65,_EU_0x56,_END_, //Russia
	  0x53,0x00,0x55,0x00,0x56,0x00,0x57,_END_, 
	  0x82,0x00,0x83,0x00,0x34,0x00,0x8b,_END_,//

 };
 /////////////////////////////////////////////////////////////////////////////////////////
 BYTE code _tSTRING_OTHER_DISPLAY_ROTATE[] =
 {
	  _D_,_i_,_s_,_p_,_l_,_a_,_y_,_,_R_, _o_, _t_, _a_, _t_, _e_, _END_,
	  _P_, _a_, _n_, _t_, _a_, _l_, _l_, _a_,_,_G_, _i_, _r_, _a_, _r_, _END_,
	  _S_, _e_, _l_, _o_, _n_,_,_T_, _o_, _u_, _r_, _n_, _e_,_r_, _END_,
	  _B_,_i_,_l_,_d_,_s_,_h_,_r_,_i_,_m_, _,_D_, _r_, _e_, _h_, _e_, _n_, _END_,
	  _S_,_c_,_h_,_e_,_r_,_m_,_o_,_,_R_, _u_, _o_, _t_, _a_, _r_,_e_, _END_,
	  _S_, _c_, _h_, _e_, _r_, _m_,_,_D_, _r_, _a_, _a_, _i_, _e_,_n_, _END_,
	  _EU_0x44,0x5e,0x43,0x5e,0x5f,0x5e,0x27,_,0x54,0x64,0x5f,0x61,0x53,0x61,_END_, // Russia (����Ӭ���� ��ܬ�Ѭ߬�)
	  _D_,_i_,_s_,_p_,_l_,_a_,_y_,_,_R_, _o_, _t_, _a_, _t_, _e_, _END_,
	  0x82,0x00,0x83,0x00,0x84,0x00,0x85,_END_,
 };


 BYTE code _tSTRING_OTHER_LOW_BLUE[] =
 {
	  _L_,_o_,_w_,_,_B_,_l_,_u_,_e_,_END_,
	  _L_,_o_,_w_,_,_B_,_l_,_u_,_e_,_END_,
	  _L_,_o_,_w_,_,_B_,_l_,_u_,_e_,_END_,
	  _L_,_o_,_w_,_,_B_,_l_,_u_,_e_,_END_,
	  _L_,_o_,_w_,_,_B_,_l_,_u_,_e_,_END_,
	  0x16,0x19,0x21,0x00,0x0c, 0x16,0x1F,0x0F,_END_,
	  0x5e,0x00,0x48,0x00,0x5f,_END_, 
	 0x60,0x00,0x47,0x00,0x61,_END_,
		  0x60,0x00,0x47,0x00,0x61,_END_,
 };

 BYTE code _tSTRING_OTHER_OVER_DRIVE[] =
 {
	  _O_,_v_,_e_,_r_,_d_,_r_,_i_,_v_,_e_,_END_,
	  _O_,_v_,_e_,_r_,_d_,_r_,_i_,_v_,_e_,_END_,
	  _O_,_v_,_e_,_r_,_d_,_r_,_i_,_v_,_e_,_END_,
	  _O_,_v_,_e_,_r_,_d_,_r_,_i_,_v_,_e_,_END_,
	  _O_,_v_,_e_,_r_,_d_,_r_,_i_,_v_,_e_,_END_,
	  _O_,_v_,_e_,_r_,_d_,_r_,_i_,_v_,_e_,_END_,
	  0x19,0x20,0x0F,0x1C,0x00,0x0E,0x1C,0x13,0x20,0x0F,0x1C,_END_, // Russia
	  0x58,0x00,0x59,0x00,0x5a,0x00,0x5b,_END_, 
	  0x60,0x00,0x61,0x00,0x62,0x00,0x63,_END_, //
 };

 BYTE code _tSTRING_OTHER_FREESYNC[] =
 {
	  _F_,_r_,_e_,_e_,_S_,_y_,_n_,_c_,_END_,
	  _F_,_r_,_e_,_e_,_S_,_y_,_n_,_c_,_END_,
	  _F_,_r_,_e_,_e_,_S_,_y_,_n_,_c_,_END_,
	  _F_,_r_,_e_,_e_,_S_,_y_,_n_,_c_,_END_,
	  _F_,_r_,_e_,_e_,_S_,_y_,_n_,_c_,_END_,
	  0x10,0x1c,0x0f,0x0f,0x1d,0x23,0x18,0x0d,_END_,
	  0x10,0x1c,0x0f,0x0f,0x1d,0x23,0x18,0x0d,_END_,
	 0x10,0x1c,0x0f,0x0f,0x1d,0x23,0x18,0x0d,_END_,
		  0x10,0x1c,0x0f,0x0f,0x1d,0x23,0x18,0x0d,_END_,
 };
 BYTE code _tSTRING_OTHER_FULLSCREEN[] =
 {
	  _F_,_u_,_l_,_l_,_,_S_,_c_,_r_,_e_,_e_,_n_,_END_,
	  //_P_,_a_,_n_,_t_,_a_,_l_,_l_,_a_,_,_C_,_o_,_m_,_p_,_l_,_e_,_t_,_a_,_END_,
	  _P_,_a_,_n_,_t_,_a_,_l_,_l_,_a_,_,_C_,_o_,_DOT_,_END_,
	  _P_,_l_,_e_,_i_,_n_,_,_e1_,_c_,_r_,_a_,_n_,_END_,
	  _V_,_o_,_l_,_l_,_b_,_i_,_l_,_d_,_END_,
	  //_S_,_c_,_h_,_e_,_r_,_m_,_n_,_o_,_,_I_,_n_,_t_,_e_,_r_,_o_,_END_,
	  _S_,_c_,_h_,_e_,_r_,_m_,_n_,_o_,_,_I_,_n_,_DOT_,_END_,
	  _V_,_o_,_l_,_l_,_e_,_d_,_i_,_g_,_,_S_,_c_,_h_,_e_,_r_,_m_, _END_,
	  0x44, 0x5E, 0x5A, 0x53, 0x5E, 0x3A, 0x64, 0x5F, 0x61, 0x53, 0x53, 0x3B, 0x66, _END_,   //Russia   
	  0x5f,0x00,0x7c,0x00,0x53,0x00,0x55,_END_, 
	  0x64,0x00,0x65,_END_, //
 };
 BYTE code _tSTRING_OTHER_AUTO[] =
 {
	  _A_,_u_,_t_,_o_,_END_,
	  _a_,_u_,_t_,_o_,_m_,_a_,_t_,_i_,_c_,_o_,_END_,    
	  _A_,_u_,_t_,_o_,_m_,_a_,_t_,_i_,_q_,_u_,_e_,_END_,	
	  _A_,_u_,_t_,_o_,_m_,_a_,_t_,_i_,_s_,_c_,_h_,_e_,_END_,	
	  _A_,_u_,_t_,_o_,_m_,_a_,_t_,_i_,_c_,_a_,_END_,
	  _A_,_U_,_T_,_O_,_END_,
	  0x0B, 0x43, 0x27, 0x5E, _END_,  //Russia
	  0x66,0x00,0x80,0x00,0x53,0x00,0x55,_END_, 
	  0x66,0x00,0x67,_END_, //

 };
 BYTE code _tSTRING_OTHER_4_3[] =
 {
	  _4_,_COLON_,_3_,_END_,
	  _4_,_COLON_,_3_,_END_,
	  _4_,_COLON_,_3_,_END_,
	  _4_,_COLON_,_3_,_END_,
	  _4_,_COLON_,_3_,_END_,
	  _4_,_COLON_,_3_,_END_,
	  _4_,0x26,_3_,_END_, //Russia
	  _4_,0x26,_3_,_END_,
	  _4_,0x26,_3_,_END_,//
 };

 BYTE code _tSTRING_OTHER_5_4[] =
 {
	  _5_,_COLON_,_4_,_END_,
	  _5_,_COLON_,_4_,_END_,
	  _5_,_COLON_,_4_,_END_,
	  _5_,_COLON_,_4_,_END_,
	  _5_,_COLON_,_4_,_END_,
	  _5_,_COLON_,_4_,_END_,
	  _5_,0x26,_4_,_END_, //Russia
	  _5_,0x26,_4_,_END_,
	  _5_,0x26,_4_,_END_,//
 };

 BYTE code _tSTRING_OTHER_1_1[] =
 {
	  _1_,_COLON_,_1_,_END_,
	  _1_,_COLON_,_1_,_END_,
	  _1_,_COLON_,_1_,_END_,
	  _1_,_COLON_,_1_,_END_,
	  _1_,_COLON_,_1_,_END_,
	  _1_,_COLON_,_1_,_END_,
	  _1_,0x26,_1_,_END_, //Russia
	  _1_,0x26,_1_,_END_,
	  _1_,0x26,_1_,_END_,//
 };
 //BYTE code _tSTRING_OTHER_ON[] =
 //{
	//  _O_,_n_,_END_,
	//  _S_,_i_,_END_,
	//  _M_,_a_,_r_,_c_,_h_,_e_,_END_,
	//  _E_,_i_,_n_,_END_,
	//  _O_,_n_,_END_,
	//  _A_,_a_,_n_,_END_,
	//   _B_,_EU_0x64,_EU_0x45,0x25,_END_, //Russia
	//  0x92,0x00,0x57,_END_,
	//  0x5b,_END_, 

 //};
 //BYTE code _tSTRING_OTHER_OFF[] =
 //{
	//  _O_,_f_,_f_,_END_,
	//  _N_,_o_,_END_,
	//  _A_,_r_,_r_,_e_,_t_,_END_,
	// _A_,_u_,_s_,_END_,
	//  _O_,_f_,_f_,_END_,
	//   _U_,_i_,_t_,_END_,
	//   _B_,_EU_0x3B,_EU_0x64,_EU_0x45,0x25,_END_, //Russia
	//  0x69,0x00,0x57,_END_,
	//  0x40,_END_, 	 
 //};
#if 0
 BYTE code _tSTRING_OTHER_WEAK[] =
 {
	  _W_,_e_,_a_, _k_,_END_,
	 _D_,_e2_,_b_,_i_,_l_,_END_,    
	  _F_,_a_,_i_,_b_,_l_,_e_,_END_,	
	  _S_,_c_,_h_,_w_,_a_,_c_,_h_,_END_,	
	  _D_,_e_,_b_,_o_,_l_,_e_,_END_,	
	  0x6b,0x00,0x6c,_END_,
		  0x41,_END_, 
	 0x40,_END_,
		  0x40,_END_,
 };
 BYTE code _tSTRING_OTHER_MEDIAN[] =
 {
	   _M_,_e_,_d_,_i_,_a_,_n_,_END_,
	 _M_,_e_,_d_,_i_,_a_,_n_,_a_,_A2_,_END_,    
	   _M_,_e2_,_d_,_i_,_a_,_n_,_e_,_END_,	 
	   _M_,_i_,_t_,_t_,_l_,_e_,_r_,_e_,_END_,	 
	   _M_,_e_,_d_,_i_,_a_,_n_,_o_,_END_,	 
	   0x6d,0x00,0x6e,_END_,
		   0x42,_END_, 
	 0x41,_END_,
		   0x41,_END_,
 };
 BYTE code _tSTRING_OTHER_STRONG[] =
 {
	   _S_,_t_,_o_,_n_,_g_,_END_,
	 _F_,_u_,_e_,_r_,_t_,_e_,_END_,    
	   _F_,_o_,_r_,_t_,_END_,	 
	 _S_,_t_,_a_,_r_,_k_,_END_,
	   _F_,_o_,_r_,_t_,_e_,_END_,	 
	   0x6f,0x00,0x70,_END_,
		   0x43,_END_, 
	 0x42,_END_,
		   0x42,_END_,
 };
 BYTE code _tSTRING_OTHER_STRONGEST[] =
 {
	 _S_,_t_,_o_,_n_,_g_,_e_,_s_,_t_,_END_,
	 _M_,_a2_,_s_,___,_f_,_u_,_e_,_r_,_t_,_e_,_END_,
	 _S_,_t_,_o_,_n_,_g_,_e_,_s_,_t_,_END_,
	 _S_,_t_,_a3_,_r_,_k_,_s_,_t_,_e_,_END_,
	 _I_,_I_,_,_p_,_i_,_a_,_f_,_o_,_r_,_t_,_e_,_END_,
	 0x71,0x00,0x72,_END_,
	  0x44,0x00,0x43,_END_, 
	 0x43,0x00,0x42,_END_,
		 0x43,0x00,0x42,_END_,
 };
 
 BYTE code	*COLOR_TEMP_TABLE1[5] =
 {
	tSTRING_COLOR_TEMP_9300, tSTRING_COLOR_TEMP_6500,tSTRING_COLOR_TEMP_5800,tSTRING_COLOR_TEMP_sRGB,tSTRING_COLOR_TEMP_User,//tSTRING_OFF, tSTRING_ON,// _STRING_OFF, _STRING_ON, 
 };
#endif
 /*
#if(_USER_FUNCTION_FPS1_FPS2==_ON)
 BYTE code	*tSTRING_Color_Effect_TABLE1[6] =
 {
	tSTRING_Color_Effect_Standard, tSTRING_Color_Effect_Game,tSTRING_Color_Effect_Movie, tSTRING_Color_Effect_Photo,tSTRING_Color_Effect_FPS1,tSTRING_Color_Effect_FPS2,//tSTRING_OFF, tSTRING_ON,// _STRING_OFF, _STRING_ON, 
 };
#else
 BYTE code	*tSTRING_Color_Effect_TABLE1[7] =
 {
	tSTRING_Color_Effect_Standard, tSTRING_Color_Effect_Game,tSTRING_Color_Effect_Movie, tSTRING_Color_Effect_Photo,//tSTRING_OFF, tSTRING_ON,// _STRING_OFF, _STRING_ON, 
 
 };
#endif  
*/
#if 0
 BYTE code	*tSTRING_Gama_TABLE1[5] =
 {
	tSTRING_OFF, tSTRING_Gamma_18, tSTRING_Gamma_20,tSTRING_Gamma_22,tSTRING_Gamma_24,//tSTRING_OFF, tSTRING_ON,// _STRING_OFF, _STRING_ON, 
 };
 
 BYTE code	*tSTRING_DP_Option_TABLE1[2] =
 {
	tSTRING_DP_Option_D011,tSTRING_DP_Option_D012,// tSTRING_DP_Option_D111,tSTRING_DP_Option_D112,//tSTRING_OFF, tSTRING_ON,// _STRING_OFF, _STRING_ON, 
 };
 BYTE code	*tSTRING_DP_EDID_TABLE1[4]=
 {
	tSTRING_DP_EDID_1080P,tSTRING_DP_EDID_2560X1440,tSTRING_DP_EDID_4k2k30hz,tSTRING_DP_EDID_4k2k60hz,
 };
 BYTE code	*tSTRING_Ultra_Vivid_TABLE1[4] =
 {
	tSTRING_OFF, tSTRING_Ultra_Vivid_L, tSTRING_Ultra_Vivid_M,tSTRING_Ultra_Vivid_H,//tSTRING_OFF, tSTRING_ON,// _STRING_OFF, _STRING_ON, 
 };
 
 BYTE code	*tSTRING_Aspect_Ratio_TABLE1[5] =
 {
	tSTRING_Aspect_Ratio_full, tSTRING_Aspect_Ratio_169, tSTRING_Aspect_Ratio_43,tSTRING_Aspect_Ratio_54,tSTRING_Aspect_Ratio_11,//tSTRING_OFF, tSTRING_ON,// _STRING_OFF, _STRING_ON, 
 };
 BYTE code	*tSTRING_audio_source_TABLE1[3] =
 {
	tSTRING_Audio_Source_Analog,tSTRING_Audio_Source_Digital,  tSTRING_Audio_Source_Auto,
 };
#endif

 BYTE code tSTRING_BACKLIGHT[] =
 {
	 _B_, _a_, _c_, _k_, _l_,  _i_,_g_, _h_, _t_,  _END_,
	 _L_, _u_, _m_, _i_, _n_, _a_, _n_, _c_, _i_,_a_, _END_,
	 _L_, _u_, _m_, _i_, _r_, _e_, _END_,
	 _R_, _U0_, _c_, _k_, _l_, _i_, _c_, _h_, _t_, _END_,
	 _C_, _o_, _n_, _t_, _r_, _o_, _l_, _u_, _c_, _e_, _END_,
	 _V_, _e_, _r_, _l_, _i_, _c_, _h_, _t_, _i_, _n_, _g_, _END_,
	 0x44,0x5e, 0x56,0x60, 0x43, 0x62, 0x27, 0x64, 0x61, _END_, //Russia
	 0x31,0x00,0x32,_END_,
	 0x6F,0x00,0x5F,_END_,//
	 

//	 _B_, _r_, _i_, _g_, _h_,  _t_,_n_, _e_, _s_, _s_, _END_,
//     _B_, _r_, _i_, _l_, _l_, _O_,_END_,
//	 _L_, _u_, _m_, _i_, _n_, _o_, _s_, _i_, _t_,_e2_, _END_,
//	 _H_, _e_, _l_, _l_, _i_, _g_, _k_, _e_, _i_,_t_, _END_,
//	 _L_, _u_, _m_, _i_, _n_, _o_, _s_, _i_, _t_,_a2_, _END_,
//	 0x2f,0x00,0x2d,_END_,
//	 0x31,0x00,0x32,_END_,
//	  0x30,0x00,0x31,_END_,
//	  0x30,0x00,0x31,_END_,
 };
 
 BYTE code tSTRING_BRIGHTNESS[] =
 {
	_B_, _r_, _i_, _g_, _h_, _t_,_n_, _e_, _s_, _s_, _END_,
	_B_,_r_,_i_,_l_,_l_,_o_,_END_,
	_L_,_u_,_m_,_i_,_n_,_o_,_s_,_i_,_t_,_e1_,_END_,
	_H_,_e_,_l_,_l_,_i_,_g_,_k_,_r_,_i_,_t_,_END_,
	_L_,_u_,_m_,_i_,_n_,_o_,_s_,_i_,_t_,_a4_,_END_,
	_H_,_e_,_l_,_d_,_e_,_r_,_h_,_e_,_i_,_d_,_END_,
	_EU_0x70,_EU_0x5F,_EU_0x64,_EU_0x5E,_EU_0x60,0x27,_EU_0x3C,_END_, //Russia
	_B_, _r_, _i_, _g_, _h_, _t_,_n_, _e_, _s_, _s_, _END_,
	0x31,0x00,0x32,_END_,//
 };

 BYTE code tSTRING_CONTRAST[] =
 {
	 _C_, _o_, _n_, _t_, _r_, _a_, _s_, _t_, _END_,
	 _C_, _o_, _n_, _t_, _r_, _a_, _s_, _t_, _END_,
	 _C_, _o_, _n_, _t_, _r_, _a_, _s_, _t_,_e_, _END_,
	 _K_, _o_, _n_, _t_, _r_, _a_, _s_, _t_, _END_,
	 _C_, _o_, _n_, _t_, _r_, _a_, _s_, _t_,_o_, _END_,
	 _C_,_o_,_n_,_t_,_r_,_a_,_s_,_t_,_END_,
	 _EU_0x46,_EU_0x5E,_EU_0x53,0x27,_EU_0x5F,_EU_0x61,_EU_0x60,0x27,_END_, //Russia
	 0x31,0x00,0x32,0x00,0x33,_END_,
	 0x33,0x00,0x34,0x00,0x32,_END_,//
	
 };
 BYTE code tSTRING_ECO[] =
 {
	 _E_, _C_, _O_, _END_,
	 _E_, _C_, _O_, _END_,
	 _E_, _C_, _O_, _END_,
	 _E_, _C_, _O_, _END_,
	 _E_, _C_, _O_, _END_,
	 0x0f,0x0d,0x19,_END_,
	 0x0f,0x0d,0x19,_END_,
		0x0f,0x0d,0x19,_END_,
		 0x0f,0x0d,0x19,_END_,
 };
 
 BYTE code tSTRING_MAINSR[] =
 {
	 _M_, _a_, _i_, _n_, ___, _S_, _R_, _END_,
	 _M_, _a_, _i_, _n_, ___, _S_, _R_, _END_,
	 _M_, _a_, _i_, _n_, ___, _S_, _R_, _END_,
	 _M_, _a_, _i_, _n_, ___, _S_, _R_, _END_,
	 _M_, _a_, _i_, _n_, ___, _S_, _R_, _END_,
	 0x17,0x0b,0x13,0x18,0x00,0x1d,0x1c,_END_,
	  0x35,0x00,0x36,_END_,
	0x17,0x0b,0x13,0x18,0x00,0x1d,0x1c,_END_,
	0x17,0x0b,0x13,0x18,0x00,0x1d,0x1c,_END_,
 };
 BYTE code _tSTRING_COLOR_STANDARD[] =
 {
 	 _S_, _t_, _a_, _n_, _d_, _a_, _r_, _d_, _END_,
	 _E_, _s_, _t_, _a2_, _n_, _d_, _a_, _r_, _END_,
	 _S_, _t_, _a_, _n_, _d_, _a_, _r_, _d_, _END_,
	 _S_, _t_, _a_, _n_, _d_, _a_, _r_, _d_, _END_,
	 _S_, _t_, _a_, _n_, _d_, _a_, _r_, _d_, _END_,
	 _S_, _t_, _a_, _n_, _d_, _a_, _r_, _d_, _END_,
	 _C_,0x27,_EU_0x61,_EU_0x53,_EU_0x56,_EU_0x61,_EU_0x5F,0x27,_EU_0x53,_EU_0x3B,_EU_0x66,_END_, //Russia
	 0x5c,0x00,0x5d,_END_,
	 0x37,0x00,0x38,_END_, //
 };

 BYTE code _tSTRING_COLOR_MOVIE[] =
 {
	 _M_, _o_, _v_, _i_, _e_, _END_,
	 _P_, _e_, _l_, _I0_, _c_, _u_, _l_, _a_, _END_,
	 _F_, _i_, _l_, _m_, _END_,
	 _F_, _i_, _l_, _m_, _END_,
	 _F_, _i_, _l_, _m_, _END_,
	 _M_, _o_, _v_, _i_, _e_, _END_,
	 _M_,_O_,_V_,_I_,_E_,_END_, //Russia
	 0x5e,0x00,0x53,_END_, 
	 0x39,0x00,0x3a,_END_, //
 };
 BYTE code _tSTRING_COLOR_PHOTO[] =
 {
	 _P_, _h_, _o_, _t_, _o_,_END_,
	 _F_, _o_, _t_, _o_,_A2_,_END_,
	 _P_, _h_, _o_, _t_, _o_,_END_,
	 _F_, _o_,_t_, _o_,_END_,
	 _F_, _o_,_t_, _o_,_END_,
	 _F_, _o_,_t_, _o_,_END_,
	 0x42,0x5e,0x27,0x5e, _END_, //Russia
	0x60,0x00,0x61,_END_,
	 0x9e,0x00,0x3b,_END_,//
		
 };
 BYTE code _tSTRING_COLOR_GAME[] =
 {
	 _G_, _a_, _m_, _e_,_END_,
	 _G_, _a_, _m_, _e_,_END_,
	 _J_, _e_, _u_, _END_,
	 _S_, _p_, _i_, _e_, _l_, _END_,
	 _G_,_i_,_o_,_c_,_o_,_END_, 
	 _G_, _a_, _m_, _e_,_END_,
	 _G_, _A_, _M_, _E_,_END_, //Russia
	 0x3c,0x00,0x3d,_END_,//
	 0x3c,0x00,0x3d,_END_,//
 };
 BYTE code _tSTRING_COLOR_VIVID[] =
 {
  _V_,  _i_,  _v_,  _i_, _d_, _END_,
  _V_,  _i_,  _v_,  _i_, _d_, _END_,
  _V_,  _i_,  _v_,  _i_, _d_, _END_,
  _V_,  _i_,  _v_,  _i_, _d_, _END_,
  _V_,  _i_,  _v_,  _i_, _d_, _END_,
  _L_,  _e_,  _v_,  _e_, _n_, _d_, _i_, _g_, _END_, 
  _V_,  _I_,  _V_,  _I_, _D_, _END_,  //Russia
  0x81,0x00,0x67, _END_,//
  0x81,0x00,0x67, _END_,//
 };

 //BYTE code _tSTRING_PICTURE_FPS[] =
 //{
	// _F_, _P_, _S_,_END_,
	// _F_, _P_, _S_,_END_,
	// _F_, _P_, _S_,_END_,
	// _F_, _P_, _S_,_END_,
	// _F_, _P_, _S_,_END_,
	// 0x10,0x1a,0x1d,_END_,
	// 0x10,0x1a,0x1d,_END_,
	//0x10,0x1a,0x1d,_END_,
	//	 0x10,0x1a,0x1d,_END_,
 //};
 //BYTE code _tSTRING_PICTURE_RTS[] =
 //{
	// _R_, _T_, _S_, _END_,
	// _R_, _T_, _S_, _END_,
	// _R_, _T_, _S_, _END_,
	// _R_, _T_, _S_, _END_,
	// _R_, _T_, _S_, _END_,
	// 0x1c,0x1e,0x1d,_END_,
	// 0x1c,0x1e,0x1d,_END_,
	//	0x1c,0x1e,0x1d,_END_,
	//	 0x1c,0x1e,0x1d,_END_,
 //};
 BYTE code _tSTRING_COLOR_USER[] =
 {
	 _U_, _s_, _e_, _r_, _END_,
	 _U_, _s_, _u_, _a_, _r_, _i_, _o_,_END_,
	 _U_, _t_, _i_, _l_, _i_, _s_, _a_,_t_, _e_, _u_, _r_,_END_,
	 _B_, _e_, _n_, _u_, _t_, _z_, _e_,_r_,_END_,
	 _U_, _t_, _e_, _n_, _t_, _e_,_END_,
	 _G_,_e_,_b_,_r_,_u_,_i_,_k_,_e_,_r_,_END_,
	 _EU_0x44,_EU_0x5E,_EU_0x45,_EU_0x3C,_EU_0x3A,_DOT_,_END_, //Russia
	  0x11,0x0b,0x17,0x0f,_END_,
	  0x3c,0x00,0x3b,0x00,0x27,0x00,0x37,_END_,
 };
#if 0
 BYTE code _tSTRING_GAME_MENU[] =
 {
	 _G_, _A_, _M_, _E_,___, _M_, _E_, _N_, _U_,_END_,
	 _G_, _A_, _M_, _E_,___, _M_, _E_, _N_, _U_,_END_,
	 _G_, _A_, _M_, _E_,___, _M_, _E_, _N_, _U_,_END_,
	 _G_, _A_, _M_, _E_,___, _M_, _E_, _N_, _U_,_END_,
	 _G_, _A_, _M_, _E_,___, _M_, _E_, _N_, _U_,_END_,
	 0x11,0x0b,0x17,0x0f,_END_,
	  0x3c,0x00,0x3b,0x00,0x27,0x00,0x37,_END_,
		0x3c,0x00,0x3d,_END_,
		 0x3c,0x00,0x3d,_END_,
 };
 BYTE code _tSTRING_GAME_TIME[] =
 {
	 _G_, _A_, _M_, _E_,___, _T_, _I_, _M_, _E_,_END_,
	 _G_, _A_, _M_, _E_,___, _T_, _I_, _M_, _E_,_END_,
	 _G_, _A_, _M_, _E_,___, _T_, _I_, _M_, _E_,_END_,
	 _G_, _A_, _M_, _E_,___, _T_, _I_, _M_, _E_,_END_,
	 _G_, _A_, _M_, _E_,___, _T_, _I_, _M_, _E_,_END_,
	0x8d,0x00,0x8e,0x00,0x8f,_END_,
	 //0x11,0x0b,0x17,0x0f,_END_,
	 0x3c,0x00,0x3b,0x00,0x52,0x00,0x53,_END_,
		0x3c,0x00,0x3d,_END_,
		 0x3c,0x00,0x3d,_END_,
 };
 BYTE code _tSTRING_GAME_CURSOR[] =
 {
	 _G_, _A_, _M_, _E_,___, _C_, _U_, _R_, _S_,_O_, _R_,_END_,
	 _C_, _O_, _N_, _T_, _R_, _A_, _S_, _T_,  _E_,_END_,
	 _K_, _O_, _N_, _T_, _R_, _A_, _S_, _T_, _END_,
	  _C_, _O_, _N_, _T_, _R_, _A_, _S_, _T_, _E_, _END_,
	  _C_, _O_, _N_, _T_, _R_, _A_, _S_, _T_, _O_, _END_,
	 0x0d,0x1c,0x19,0x1d,0x1d,0x12,0x0b,0x13,0x1c,_END_,
		0x3c,0x00,0x3d,_END_,
		 0x3c,0x00,0x3d,_END_,
 };
 BYTE code _tSTRING_GAME_TIMER_POSITION[] =
 {
	 _P_, _O_, _S_, _I_,_T_, _I_, _O_, _N_,_END_,
	 _C_, _O_, _N_, _T_, _R_, _A_, _S_, _T_,  _E_,_END_,
	 _K_, _O_, _N_, _T_, _R_, _A_, _S_, _T_, _END_,
	  _C_, _O_, _N_, _T_, _R_, _A_, _S_, _T_, _E_, _END_,
	  _C_, _O_, _N_, _T_, _R_, _A_, _S_, _T_, _O_, _END_,
	 _C_, _O_, _N_, _T_, _R_, _A_, _S_, _T_, _END_,
	  0x1a,0x00,0x3a,0x00,0x19,_END_,
		0x3c,0x00,0x3d,_END_,
		 0x3c,0x00,0x3d,_END_,
 };

 BYTE code _tSTRING_PICTURE_OFF[] =
 {
	 _O_, _f_, _f_, _END_,
	 _C_, _O_, _N_, _T_, _R_, _A_, _S_, _T_,  _E_,_END_,
	 _K_, _O_, _N_, _T_, _R_, _A_, _S_, _T_, _END_,
	  _C_, _O_, _N_, _T_, _R_, _A_, _S_, _T_, _E_, _END_,
	  _C_, _O_, _N_, _T_, _R_, _A_, _S_, _T_, _O_, _END_,
	 0x69,0x00,0x2d,_END_,
	 0x40,_END_,
	0x3e,0x00,0x3f,_END_,
		 0x3e,0x00,0x3f,_END_,
 };
  BYTE code _tSTRING_PICTURE_WEAK[] =
 {
	 _W_, _e_, _a_, _k_, _END_,
	 _C_, _O_, _N_, _T_, _R_, _A_, _S_, _T_,  _E_,_END_,
	 _K_, _O_, _N_, _T_, _R_, _A_, _S_, _T_, _END_,
	  _C_, _O_, _N_, _T_, _R_, _A_, _S_, _T_, _E_, _END_,
	  _C_, _O_, _N_, _T_, _R_, _A_, _S_, _T_, _O_, _END_,
	 0x6b,0x00,0x6c,_END_,
	 0x41,_END_,
	0x40,_END_,
		 0x40,_END_,
 };
   BYTE code _tSTRING_PICTURE_MEDIAN[] =
 {
	 _M_, _e_, _d_, _i_, _a_, _n_, _END_,
	 _C_, _O_, _N_, _T_, _R_, _A_, _S_, _T_,  _E_,_END_,
	 _K_, _O_, _N_, _T_, _R_, _A_, _S_, _T_, _END_,
	  _C_, _O_, _N_, _T_, _R_, _A_, _S_, _T_, _E_, _END_,
	  _C_, _O_, _N_, _T_, _R_, _A_, _S_, _T_, _O_, _END_,
	 0x6d,0x00,0x6e,_END_,
	 0x42,_END_,
	0x41,_END_,
		 0x41,_END_,
 };
    BYTE code _tSTRING_PICTURE_STRONG[] =
 {
	 _S_, _t_, _r_, _o_,_n_, _g_, _END_,
	 _C_, _O_, _N_, _T_, _R_, _A_, _S_, _T_,  _E_,_END_,
	 _K_, _O_, _N_, _T_, _R_, _A_, _S_, _T_, _END_,
	  _C_, _O_, _N_, _T_, _R_, _A_, _S_, _T_, _E_, _END_,
	  _C_, _O_, _N_, _T_, _R_, _A_, _S_, _T_, _O_, _END_,
	 0x6f,0x00,0x70,_END_,
	 0x43,_END_,
	0x42,_END_,
		 0x42,_END_,
 };
	BYTE code _tSTRING_PICTURE_STRONGEST[] =
	{
		_S_, _t_, _r_, _o_, _n_, _g_, _e_, _s_, _t_,_END_,
		_C_, _O_, _N_, _T_, _R_, _A_, _S_, _T_,  _E_,_END_,
		_K_, _O_, _N_, _T_, _R_, _A_, _S_, _T_, _END_,
		 _C_, _O_, _N_, _T_, _R_, _A_, _S_, _T_, _E_, _END_,
		 _C_, _O_, _N_, _T_, _R_, _A_, _S_, _T_, _O_, _END_,
		0x71,0x00,0x72,_END_,
		0x44,0x00,0x43,_END_,
	   0x43,0x00,0x42,_END_,
			0x43,0x00,0x42,_END_,
	};
#endif

 
#if(_USER_FUNCTION_LOW_BLUE_LIGHT==_ON)
 BYTE code tLOW_BLUE_LIGHT[] =
 {
	 _L_,_O_,_W_,___, _B_,_L_,_U_,_E_,_L_,_I_,_G_,_H_,_T_,_END_,
	_B_,_L_,_E_,_U_,___,_B_,_A_,_S_,_S_,_E_,_END_,
	_L_,_O_,_W_,___,_B_,_L_,_A_,_U_,_END_,
	 _L_,_U_,_Z_,___,_A_,_Z_,_U_,_L_,___,_B_,_A_,_J_,_A_,_END_,
	 _L_,_U_,_C_,_E_,___,_B_,_L_,_U_,___,_B_,_A_,_S_,_S_,_A_,_END_,
	 _W_,_DOWNDOT_,_B_,_L_,_A_,_U_,_W_,___,_L_,_I_,_C_,_H_,_T_,_END_,
   0x4f,0x00,0x0f,0x00,0x7b,0x00,0x7a,_END_,
	0x67,0x00,0x55,0x00,0x77,_END_,
	0x67,0x00,0x55,0x00,0x77,_END_,
 };
#endif   
 
  BYTE code _tICON_CHOOSE[] =
 {
	0x6D,0x6E,_END_,
	0x6D,0x6E,_END_,
	0x6D,0x6E,_END_,
	0x6D,0x6E,_END_,
	0x6D,0x6E,_END_,
	0x6D,0x6E,_END_,
	0x6D,0x6E,_END_,
	0x6D,0x6E,_END_,
	0x6D,0x6E,_END_,
  
  };
 BYTE code tSTRING_PICTURE[] =
{
	 _P_, _i_, _c_, _t_, _u_, _r_, _e_, _END_,
	 _L_,_u_, _m_, _i_,_n_, _a_, _n_, _c_, _i_, _a_,_END_,
	 _L_,_u_, _m_, _i_,_n_, _o_, _s_, _i_, _t_, _e2_,_END_,
	 _L_,_e_, _u_, _c_,_h_, _t_, _k_, _r_, _a_, _f_,_t_,_END_,
	 _L_,_u_, _m_, _i_,_n_, _o_, _s_, _i_, _t_, _a2_,_END_,
	 _B_, _l_, _e_, _e_, _d_, _END_,
	 _EU_0x46, 0x61, 0x5F, 0x27, 0x65, 0x53, 0x61, _END_, //Russia 
	 0x27,0x00,0x28,_END_,
	 0x27,0x00,0x28,_END_,//
 
 };

	 
 BYTE code tSTRING_DISPLAY[] =
{
	_D_, _I_, _S_, _P_, _L_, _A_, _Y_, _END_,
	_S_, _E_, _L_, _O_, _N_, _END_,
	_Z_, _E_, _I_, _G_, _E_, _N_,_END_,
	_P_,_A_,_N_,_T_,_A_,_L_,_L_,_A_,_END_,
	_V_,_I_,_S_,_U_,_A_,_L_,_I_,_Z_,_Z_,_A_,_Z_,_DOWNDOT_,_END_,
	_S_,_C_,_H_,_E_,_R_,_M_,_END_,	
	_EU_0x44,0x5e, 0x43,0x5e,0x5f,0x5e,0x27,_END_, //Russia
	0x15,0x00,0x42,0x00,0x72,0x00,0x73,0x00,0x37,_END_,
	0x11,0x00,0x12,_END_,

};
	 
 BYTE code tSTRING_COLOR[] =
{
	_C_, _o_, _l_, _o_, _r_, _END_,
	_C_, _o_, _l_, _o_, _r_, _END_,
	_C_, _o_, _l_, _o_, _r_, _END_,
	_F_,_a_,_r_,_b_,_e_,_END_,
	_C_, _o_, _l_, _o_, _r_,_e_, _END_,
	_K_, _l_, _e_, _u_, _r_,_END_,
	_EU_0x41, 0x43, 0x62, 0x27, _END_, //Russia
	0x29,0x00,0x28,_END_,
	0x29,0x00,0x2a,_END_,//
};
 
 BYTE code tSTRING_ADVANCE[] =
 {
	 _O_, _S_, _D_,0x00, _S_, _e_, _t_, _t_,_i_, _n_, _g_, _s_, _END_,
	 _A_, _j_, _u_, _s_, _t_, _e_, _s_,0x00,_O_, _S_, _D_, _END_,	
	 _R_, _e2_, _g_, _l_, _a_, _g_, _e_,_s_,0x00,_O_, _S_, _D_, _END_,	
	 _O_, _S_, _D_,0x00, _E_, _i_, _n_, _s_,_t_, _e_, _l_, _l_, _DOT_, _END_,
	 _I_, _m_, _p_, _o_, _s_, _t_, _a_,_z_,_i_, _o_, _n_,_i_,_DOT_, _END_,	
	 _O_, _S_, _D_,0x00, _I_, _n_, _s_, _t_,_e_, _l_, _l_, _i_, _n_,_g_,_DOT_, _END_,
	 0x19, 0x1D, 0x0E, 0x00, 0x12,0x61,0x60,0x27,0x5F,0x5E,0x25, _END_, //Russia (OSD H�Ѭ����۬ܬ�)
	 0x19,0x1d,0x0e,_END_,
	 0x82,0x00,0x83,0x00,0x2b,0x00,0x2c,0x00,0x2d,0x00,0x2e,_END_, //
 };

 BYTE code tSTRING_SETUP[] =
 {
	 _S_, _e_, _t_, _u_, _p_, _END_,
	  _C_, _o_, _n_, _f_, _i_, _g_, _u_, _r_, _a_, _r_,_END_, 
	 _C_, _o_, _n_, _f_, _i_, _g_, _u_, _r_, _a_, _t_,_i_, _o_, _n_,_END_, 
	 _E_, _i_, _n_, _r_, _i_, _c_, _h_, _t_, _u_, _n_,_g_, _END_, 
	 _C_, _o_, _n_, _f_, _i_, _g_, _u_, _r_, _a_, _z_,_i_, _o_, _n_, _e_,_END_, 
	 _I_, _n_, _s_, _t_,_e_, _l_, _l_, _i_, _n_,_g_,_e_,_n_, _END_,
	 0x12,0x61, 0x60, 0x27, 0x5F,0x5E,0x65,0x27,0x3C, _END_, // Russia (���Ѭ����ڬ��)
	 0x2b,0x00,0x2c,_END_,
	 0x2d,0x00,0x2e,_END_,//
 };
	 
 BYTE code tSTRING_AUDIO[] =
 {
	 _V_, _o_, _l_, _u_, _m_, _e_, _END_,
	 _V_, _o_, _l_, _u_, _m_, _e_, _END_,
	 _V_, _o_, _l_, _u_, _m_, _e_, _END_,
	 _V_, _o_, _l_, _u_, _m_, _e_, _END_,
	 _V_, _o_, _l_, _u_, _m_, _e_, _END_,
	 _V_, _o_, _l_, _u_, _m_, _e_, _END_,
	 _EU_0x57,0x5F,0x5E,0x5C,0x64,0x5E,0x60,0x27,0x3c,_END_, //Russia (�����ެܬ����)
	 0x2b,0x00,0x2c,_END_,
	 0x2d,0x00,0x2e,_END_,

 };
	 
 BYTE code tSTRING_OTHER[] =
 {
	 _O_, _t_, _h_, _e_, _r_, _s_, _END_,
	 _O_, _t_, _h_, _e_, _r_, _s_, _END_,
	 _O_, _t_, _h_, _e_, _r_, _s_, _END_,
	 _O_, _t_, _h_, _e_, _r_, _s_, _END_,
	 _O_, _t_, _h_, _e_, _r_, _s_, _END_,
	 _O_, _t_, _h_, _e_, _r_, _s_, _END_,
	 _EU_0x56,0x5F, 0x63,0x58,0x65,0x62,_END_, // Russia (�լ��Ԭڬ�) 
	 0x2d,0x00,0x2e,_END_,
	 0x2f,0x00,0x30,_END_,
  };

 BYTE code tSTRING_SERVICE[] =
 {
	_S_, _e_,_r_, _v_, _i_, _c_, _e_,_END_,
	_S_, _e_,_r_, _v_, _i_, _c_, _e_,_END_,
	_S_, _e_,_r_, _v_, _i_, _c_, _e_,_END_,
	_S_, _e_,_r_, _v_, _i_, _c_, _e_,_END_,
	_S_, _e_,_r_, _v_, _i_, _c_, _e_,_END_,
	_S_, _e_,_r_, _v_, _i_, _c_, _e_,_END_,
	_S_, _E_,_R_, _V_, _I_, _C_, _E_,_END_, // Russia
	_S_, _e_,_r_, _v_, _i_, _c_, _e_,_END_,
	_S_, _e_,_r_, _v_, _i_, _c_, _e_,_END_,

 };
		 
 BYTE code tSTRING_INFORMATION[] =
 {
	 _I_, _N_, _F_, _O_, _R_, _M_, _A_, _T_, _I_, _O_, _N_, _END_,
	 _I_, _N_, _F_, _O_, _R_, _M_, _A_, _T_, _I_, _O_, _N_,_S_, _END_,
	 _I_, _N_, _F_, _O_, _R_, _M_, _A_, _T_, _I_, _O_, _N_, _END_,
	  _I_, _N_, _F_, _O_, _R_, _M_, _A_, _C_, _I_, _O3_, _N_, _END_,
	  _I_, _N_, _F_, _O_, _R_, _M_, _A_, _Z_, _I_, _O_, _N_, _I_, _END_,
	  _I_, _N_, _F_, _O_, _R_, _M_, _A_, _T_, _I_, _E_, _END_,	  
	 0x1e,0x00,0x4a,_END_,
	 0x4e,0x00,0x4f,_END_,
	 0x4e,0x00,0x4f,_END_,
  };
	 
 BYTE code tSTRING_FACTORY[] =
 {
	 _F_, _A_, _C_, _T_, _O_, _R_, _Y_, _END_,
	_U_, _S_, _I_, _N_, _E_, _END_, 
	_F_, _A_, _B_, _R_, _I_, _K_,_END_, 
	 _F_, _A_, _C_, _T_, _O_, _R_, _Y_, _END_,
	 _F_, _A_, _C_, _T_, _O_, _R_, _Y_, _END_,
	 _F_, _A_, _C_, _T_, _O_, _R_, _Y_, _END_,
	0x4b,0x00,0x4c,_END_,
	 0x50,0x00,0x51,_END_,
	 0x50,0x00,0x51,_END_,
  };
 
 BYTE code tSTRING_SHARPNESS[] =
 {
	 _S_, _h_, _a_, _r_, _p_, _n_, _e_, _s_, _s_, _END_,
	  _F_, _i_, _n_, _e_, _s_, _s_, _e_, _END_,    
	 _S_, _c_, _h_, _A0_, _r_, _f_, _e_, _END_, 
	 _N_, _i_, _t_, _i_, _d_, _e_, _z_,_END_,
	 _N_, _i_, _t_, _i_, _d_, _e_, _z_, _z_, _a_, _END_,
	 _S_, _c_, _h_, _e_, _r_, _p_, _t_, _e_, _END_,
	 0x19,0x60,0x27,0x5F,0x5E,0x27,0x61,_END_, // Russia (���������)
	 0x78,0x00,0x79,0x00,0x19,_END_,
	 0x70 ,0x00,0x32,_END_,//
  };
 
 BYTE code tSTRING_AUTO_ADJUST[] =
 {
	 _A_, _U_, _T_, _O_, ___, _A_, _D_, _J_, _U_, _S_, _T_, _END_,
	  _R_, _e1_, _G_,_L_, _A_, _G_, _E_, ___,  _A_, _U_, _T_, _O_, _END_,
	   _A_, _U_, _T_, _O_, _DOWNDOT_,___, _E_, _I_, _N_, _S_, _T_, _E_, _L_, _L_, _DOWNDOT_,_END_,
		_A_, _J_, _U_, _S_, _T_, _E_, ___, _A_, _U_, _T_, _O_, _DOWNDOT_, _END_,
	   _R_, _E_, _G_, _DOWNDOT_, _A_, _U_, _T_, _O_, _END_,
	   _A_, _U_, _T_, _O_, ___, _A_, _A_, _N_, _P_,_DOWNDOT_, _END_,
	   0x1c,0x00,0x1d,0x00,0x1b,0x00,0x27,_END_,
	  0x13, 0x00,0x14 ,0x00,0x15, 0x00,0x16, _END_,
	  0x13, 0x00,0x14 ,0x00,0x15, 0x00,0x16, _END_,
  };
 
 BYTE code tSTRING_HPOS[] =
 {
	 _H_, ___, _P_, _O_, _S_, _I_, _T_, _I_, _O_, _N_, _END_,
	  _P_, _O_, _S_, _I_, _T_, _I_, _O_, _N_, _SLINE_, _H_,_END_,
	 _H_, _SLINE_, _P_, _O_, _S_, _I_, _T_, _I_, _O_, _N_,_END_,
	  _P_, _O_, _S_, _I_, _C_, _I_, _O3_, _N_, ___, _H_, _END_,
	  _P_, _O_, _S_, _I_, _Z_, _I_, _O_, _N_, _E_, ___, _O_, _R_, _DOWNDOT_, _END_,
	  _H_, _DOWNDOT_, _P_, _O_, _S_, _I_, _T_, _I_, _E_, _END_,
	 0x1f,0x00,0x20,0x00,0x21,0x00,0x22,_END_,
	 0x17 ,0x00,0x18, 0x00,0x19, 0x00,0x1a ,_END_,
	 0x17 ,0x00,0x18, 0x00,0x19, 0x00,0x1a ,_END_,
 };
 
 BYTE code tSTRING_VPOS[] = 
 {
	 _V_, ___, _P_, _O_, _S_, _I_, _T_, _I_, _O_, _N_, _END_,
	  _P_, _O_, _S_, _I_, _T_, _I_, _O_, _N_, _SLINE_, _V_,_END_,
	 _V_, _SLINE_, _P_, _O_, _S_, _I_, _T_, _I_, _O_, _N_,_END_,
	  _P_, _O_, _S_, _I_, _C_, _I_, _O3_, _N_, ___, _V_, _END_,
	  _P_, _O_, _S_, _I_, _Z_, _I_, _O_, _N_, _E_, ___, _V_, _E_, _R_,_DOWNDOT_, _END_,
	  _V_, _DOWNDOT_, _P_, _O_, _S_, _I_, _T_, _I_, _E_, _END_,
	 0x1f,0x00,0x23,0x00,0x21,0x00,0x22,_END_,
	 0x1b,0x00,0x1c,0x00,0x19,0x00,0x1a,_END_,
	 0x1b,0x00,0x1c,0x00,0x19,0x00,0x1a,_END_,
 };
 
 BYTE code tSTRING_CLOCK[] =
 {
	 _C_, _L_, _O_, _C_, _K_, _END_,
	  _H_, _O_, _R_, _L_, _O_, _G_, _E_, _END_, 	 
	   _T_, _A_, _K_, _T_, _END_,
		_R_, _E_, _L_, _O_, _J_, _END_,
		_O_, _R_, _O_, _L_, _O_, _G_, _I_, _O_, _END_,
		_K_, _L_, _O_, _K_, _I_, _N_, _S_, _T_, _DOWNDOT_,_END_,
	   0x24,0x00,0x25,_END_,
	  0x1d, 0x00,0x1e, _END_,
	  0x1d, 0x00,0x1e, _END_,
 };
 
 BYTE code tSTRING_PHASE[] =
 {
	 _P_, _H_, _A_, _S_, _E_, _END_,
	 _M_, _I_, _S_, _E_, ___, _A_, _U_, ___, _P_, _O_, _I_, _N_, _T_, _END_,   
	 _F_, _O_, _K_, _U_, _S_, _END_, 
	  _F_, _A_, _S_, _E_, _END_,
	  _F_, _A_, _S_, _E_, _END_,
	  _F_, _A_, _S_, _E_, _END_,
	 0x21,0x00,0x27,_END_,
   0x1f ,0x00,0x19,_END_,
   0x1f ,0x00,0x19,_END_,
   };
 
 BYTE code tSTRING_GAMMA[] =
 {
	 _G_, _a_, _m_, _m_, _a_, _END_,
	 _G_, _a_, _m_, _m_, _a_, _END_,
	 _G_, _a_, _m_, _m_, _a_, _END_,
	 _G_, _a_, _m_, _m_, _a_, _END_,
	 _G_, _a_, _m_, _m_, _a_, _END_,
	 _G_, _a_, _m_, _m_, _a_, _END_,
	 _G_, _A_, _M_, _M_, _A_, _END_, // Russia
	 0x7a,0x00,0x63,_END_,
	 0x79,0x00,0x32,_END_,//
 
 };
 
 BYTE code tSTRING_COLOR_TEMP[] =
 {
	 _T_, _e_, _m_, _p_, _e_, _r_, _a_, _t_, _u_, _r_, _e_, _END_,
	  _C_, _o_, _u_, _l_, _e_, _u_, _r_, _END_,    
	 _F_, _a_, _r_, _b_, _t_, _e_, _m_, _p_, _DOWNDOT_, _END_,
	  _T_, _e_, _m_, _p_, _e_, _r_, _a_, _t_, _u_, _r_, _a_, _END_,
	  _T_, _e_, _m_, _p_, _e_, _r_, _a_, _t_, _u_, _r_, _a_, _END_,
	  _T_, _e_, _m_, _p_, _e_, _r_, _a_, _t_, _u_, _u_, _r_, _END_,
	 0x0f,0x00, 0x2b,0x00,0x19,_END_,
	 0x22,0x00,0x24,_END_,
	 0x22,0x00,0x24,_END_, //
 };
 
 BYTE code tSTRING_COLOR_EFFECT[] =
 {
	 _C_, _o_, _l_, _o_, _r_, ___, _E_, _f_, _f_, _e_, _c_, _t_, _END_,
   _E_, _c_, _o_, _END_,  
   _o2_, _k_, _o_, _END_,  
	_E_, _f_, _e_, _c_, _t_, _o_, ___, _C_, _o_, _l_, _o_, _r_, _END_,
	_E_, _f_, _f_, _e_, _t_, _t_, _o_, ___, _C_, _o_, _l_, _o_, _r_, _e_, _END_,
	_K_, _l_, _e_, _u_, _r_, _e_, _f_, _f_, _e_, _c_, _t_,_END_,
	_C_, _O_, _L_, _O_, _R_, ___, _E_, _F_, _F_, _E_, _C_, _T_, _END_, // Russia
   0x0f,0x00,0x27, 0x00,0x2c,0x00,0x2d,_END_,
   0x29,0x00,0x2a,0x00,0x77,0x00,0x78,_END_,//
  };
 
 BYTE code tSTRING_HUE[] =
 {
	_H_, _u_, _e_, _END_,
	_T_, _e_, _i_, _n_, _t_, _e_, _END_,	
   _F_, _a_, _r_, _b_, _t_, _o_, _n_, _END_,
	_M_, _a_, _t_, _i_, _z_, _END_,
	_T_, _o_, _n_, _a_, _l_, _i_, _t_, _a2_, _END_,
	_T_, _i_, _n_, _t_, _END_,
	_EU_0x5E,0x27,0x27,0x62,0x53,0x5E,0x64, _END_, // Russia (����֬߬��)
   0x0f,0x00,0x1b,_END_,
   0x29,0x00,0x71,_END_, //
  };
 
 BYTE code tSTRING_SATURATION[] =
 {
	_S_, _a_, _t_, _u_, _r_, _a_, _t_, _i_, _o_, _n_, _END_,
	_S_, _a_, _t_, _u_, _r_, _a_, _t_, _i_, _o_, _n_,_END_,	  
	_S_, _A0_, _t_, _t_, _i_, _g_, _u_, _n_, _g_,_END_, 
	_S_, _a_, _t_, _u_, _r_, _a_, _c_, _i_, _O3_, _n_, _END_,
	_S_, _a_, _t_, _u_, _r_, _a_, _z_, _i_, _o_, _n_, _e_, _END_,
	_V_, _e_, _r_, _z_, _a_, _d_, _i_, _g_, _i_, _n_, _g_, _END_,
	_EU_0x53,0x61,0x60,0x3B,0x3D,0x62,0x53,0x65,0x62,_END_, // Russia (�߬Ѭ����֬߬ڬ�)
	0x2e,0x00,0x2f,0x00,0x19,_END_,
	0x72,0x00,0x73,0x00,0x32,_END_, 
 };
 
 BYTE code tSTRING_ASPECT_RATIO[] =
 {
	 _A_, _S_, _P_, _E_, _C_, _T_, ___, _R_, _A_, _T_, _I_, _O_, _END_,
  _F_, _O_, _R_, _M_, _A_, _T_, ___, _I_, _M_, _A_, _G_, _E_, _END_,  
  _S_, _E_, _I_, _T_, _E_, _N_, _V_, _E_, _R_, _H_, _A0_, _L_, _DOWNDOT_, _END_,
   _R_, _E_, _L_, _A_, _C_, _DOWNDOT_, _A_, _S_, _P_, _E_, _C_, _T_, _O_, _END_,
  _R_, _A_, _P_, _P_,_DOWNDOT_, _P_, _R_, _O_, _P_, _DOWNDOT_, _END_,
   _B_, _E_, _E_, _L_, _D_, _V_, _E_, _R_, _H_,_DOWNDOT_, _END_,
  0x37,0x00,0x38,0x00,0x1E,0x00, 0x3a,0x00,0x3b,_END_,
 0x0b,0x00,0x0c,0x00,0x10,0x00,0x3b,_END_,
 0x0b,0x00,0x0c,0x00,0x10,0x00,0x3b,_END_,
 };
 
 
 BYTE code tSTRING_DDCCI[] =
 {
	 _D_, _D_, _C_, _C_, _I_, _END_,
	 _D_, _D_, _C_, _C_, _I_, _END_,
	 _D_, _D_, _C_, _C_, _I_, _END_,
	 _D_, _D_, _C_, _C_, _I_, _END_,
	 _D_, _D_, _C_, _C_, _I_, _END_,
	 _D_, _D_, _C_, _C_, _I_, _END_,
	  _D_, _D_, _C_, _C_, _I_, _END_,
	 _D_, _D_, _C_, _C_, _I_, _END_,
	 _D_, _D_, _C_, _C_, _I_, _END_,
 
 };
 
 BYTE code tSTRING_ULTRA_VIVID[] =
 {
	 _U_, _L_, _T_, _R_, _A_, ___, _V_, _I_, _V_, _I_, _D_, _END_,
	 _U_, _L_, _T_, _R_, _A_,_SLINE_, _C_, _L_, _A_, _I_, _R_,	_END_,	 
	  _U_, _L_, _T_, _R_, _A_,_SLINE_, _H_, _E_, _L_, _L_, _END_,
	   _M_, _A_, _T_, _I_, _C_, _E_, _S_, ___, _I_, _N_, _T_, _E_, _N_, _DOWNDOT_,_END_, 
	 _U_, _L_, _T_, _R_, _A_, ___, _V_, _I_, _V_, _A_, _C_, _E_, _END_,
	   _E_, _X_, _T_, _R_, _A_, ___, _L_, _E_, _V_, _E_, _N_, _D_, _I_, _G_, _END_,
	 0x53,0x00,0x35,0x00,0x36,0x00,0x55,0x00,0x66,0x00,0x80,0x00,0x42,_END_,
		 0x38, 0x00,0x39,0x00,0x3a,_END_,
	 0x38, 0x00,0x39,0x00,0x3a,_END_,
 
 };
 
 BYTE code tSTRING_DP_FORMAT[] =
 {
	_D_, _P_, ___, _F_, _o_, _r_, _m_, _a_, _t_, _END_,
	_D_, _P_, ___, _F_, _o_, _r_, _m_, _a_, _t_, _END_,
	_D_, _P_, ___, _F_, _o_, _r_, _m_, _a_, _t_, _END_,
	_D_, _P_, ___, _F_, _o_, _r_, _m_, _a_, _t_, _END_,
	_D_, _P_, ___, _F_, _o_, _r_, _m_, _a_, _t_, _END_,
	_D_, _P_, ___, _F_, _o_, _r_, _m_, _a_, _t_, _END_,
	_D_, _P_, ___, _F_, _O_, _R_, _M_, _A_, _T_, _END_, // Russia
	_D_, _P_, ___, _F_, _o_, _r_, _m_, _a_, _t_, _END_,
	_D_, _P_, ___, 0x86, 0x00,0x87,_END_,//

};

 BYTE code tSTRING_DP_MST[] =
 {
	_D_, _P_, ___, _M_, _S_, _T_, _END_,
	_D_, _P_, ___, _M_, _S_, _T_, _END_,
	_D_, _P_, ___, _M_, _S_, _T_, _END_,
	_D_, _P_, ___, _M_, _S_, _T_, _END_,
	_D_, _P_, ___, _M_, _S_, _T_, _END_,
	_D_, _P_, ___, _M_, _S_, _T_, _END_,
	_D_, _P_, ___, _M_, _S_, _T_, _END_, // Russia
	_D_, _P_, ___, _M_, _S_, _T_, _END_,
	_D_, _P_, 0x7f,0x00,0x8e,0x00,0xa1,0x00,0xa2,0x00,0x94,0x00,0x55, _END_,//

 };

 BYTE code tSTRING_CLONE[] =
 {
	_C_, _l_, _o_, _n_, _e_,  ___, _M_, _o_ , _d_ , _e_, _END_,
	_C_, _l_, _o_, _n_, _e_,  ___, _M_, _o_ , _d_ , _e_, _END_,
	_C_, _l_, _o_, _n_, _e_,  ___, _M_, _o_ , _d_ , _e_, _END_,
	_C_, _l_, _o_, _n_, _e_,  ___, _M_, _o_ , _d_ , _e_, _END_,
	_C_, _l_, _o_, _n_, _e_,  ___, _M_, _o_ , _d_ , _e_, _END_,
	_C_, _l_, _o_, _n_, _e_,  ___, _M_, _o_ , _d_ , _e_, _END_,
	_C_, _L_, _O_, _N_, _E_,  ___, _M_, _O_ , _D_ , _E_, _END_, // Russia
	_C_, _l_, _o_, _n_, _e_,  ___, _M_, _o_ , _d_ , _e_, _END_,
	0x88, 0x00,0x89,0x00,0x8a,0x00,0x87, _END_,//

 };
 
	 BYTE code tSTRING_DP1_1[] =
 {
	_D_,_P_,___, _1_,_DOT_,_1_,_END_,
	_D_,_P_,___, _1_,_DOT_,_1_,_END_,
	_D_,_P_,___, _1_,_DOT_,_1_,_END_,
	_D_,_P_,___, _1_,_DOT_,_1_,_END_,
	_D_,_P_,___, _1_,_DOT_,_1_,_END_,
	_D_,_P_,___, _1_,_DOT_,_1_,_END_,
	_D_,_P_,___, _1_,0x25,_1_,_END_, // Russia
	_D_,_P_,___, _1_,0x25,_1_,_END_,
	_D_,_P_,___, _1_,0x25,_1_,_END_,//
 };

 BYTE code tSTRING_DP1_2[] =
 {
	_D_,_P_,___, _1_,_DOT_,_2_,_END_,
	_D_,_P_,___, _1_,_DOT_,_2_,_END_,
	_D_,_P_,___, _1_,_DOT_,_2_,_END_,
	_D_,_P_,___, _1_,_DOT_,_2_,_END_,
	_D_,_P_,___, _1_,_DOT_,_2_,_END_,
	_D_,_P_,___, _1_,_DOT_,_2_,_END_,
	_D_,_P_,___, _1_,0x25, _2_,_END_, // Russia
	_D_,_P_,___, _1_,0x25,_2_,_END_,
	_D_,_P_,___, _1_,0x25,_2_,_END_,//
 };

 BYTE code tSTRING_DP1[] =
 {
	_D_,_P_,___, _1_, _END_,
	_D_,_P_,___, _1_, _END_,
	_D_,_P_,___, _1_, _END_,
	_D_,_P_,___, _1_, _END_,
	_D_,_P_,___, _1_, _END_,
	_D_,_P_,___, _1_, _END_,
	_D_,_P_,___, _1_, _END_, // Russia
	_D_,_P_,___, _1_, _END_,
	_D_,_P_,___, _1_, _END_,
 };

 BYTE code tSTRING_DP2[] =
 {
	_D_,_P_,___, _2_, _END_,
	_D_,_P_,___, _2_, _END_,
	_D_,_P_,___, _2_, _END_,
	_D_,_P_,___, _2_, _END_,
	_D_,_P_,___, _2_, _END_,
	_D_,_P_,___, _2_, _END_,
	_D_,_P_,___, _2_, _END_, // Russia
	_D_,_P_,___, _2_, _END_,
	_D_,_P_,___, _2_, _END_,
 };

 BYTE code tSTRING_AUTO_SELECT[] =
 {
	 _A_,_u_,_t_,_o_,___,_S_,_e_,_l_,_e_,_c_,_t_,_END_,
	_A_,_U_,_T_,_O_,_M_,_A_,_T_,_I_,_Q_,_U_,_E_,_END_,				 
	 _A_,_U_,_T_,_O_,___,_W_,_A0_,_H_,_L_,_E_,_N_,_END_,
	  _S_, _E_, _L_, _E_, _C_, _C_, _I_, _O3_, _N_, ___, _A_, _U_, _T_, _O_, _END_,
	  _S_, _E_, _L_, _DOWNDOT_, _A_, _U_, _T_, _O_, _END_,
	  _A_, _U_, _T_, _O_, _M_,_DOWNDOT_, _S_, _E_, _L_, _E_, _C_, _T_, _DOWNDOT_,_END_,
	 0x1c,0x00,0x1d,0x00,0x32,0x00,0x3c,_END_,
	 0x13,0x00,0x14,0x00,0x36,0x00,0x3e,_END_,
	 //0x66,0x00,0x67,0x00,0x7d,0x00,0x7e,0x00,0x7f,0x00,0x56,0x00,0x69,0x00,0x6a,_END_,// �ڵ��Է� ��ȣ ��ȯ
	 0x66,0x67,0x7d,0x7e,0x55,0x56,0x69,0x6a,_END_,// �ڵ��Է� ��ȣ ��ȯ
 
 };
 
 
 BYTE code tSTRING_VOLUME[] =
 {
	 _V_, _O_, _L_, _U_, _M_, _E_, _END_, 
  _V_, _O_, _L_, _U_, _M_, _E_, _END_,	   
  _L_, _A_, _U_, _T_, _S_, _T_, _A0_, _R_, _K_, _E_, _END_,
   _V_, _O_, _L_, _U_, _M_, _E_, _N_, _END_,
   _V_, _O_, _L_, _U_, _M_, _E_, _END_,
	_V_, _O_, _L_, _U_, _M_, _E_, _END_,
  0x3d,0x00,0x3e,_END_,
	   0x3f,0x00,0x41,	_END_,
	  0x58,0x00,0x80,  _END_, //
 
 };
 
 BYTE code tSTRING_MUTE[] =
 {
	 _M_, _U_, _T_, _E_, _END_,
  _M_, _U_, _E_, _T_, _END_,  
  _S_, _T_, _U_, _M_, _M_, _END_,
  _S_, _I_, _L_, _E_, _N_, _C_, _I_, _O_, _END_,
  _M_, _U_, _T_, _E_, _END_,
   _D_, _E_, _M_, _P_, _E_, _N_,_END_,
  0x3f,0x00,0x40,0x00,0x41,_END_,
   0x42, 0x00,0x3f,_END_,
  0x42, 0x00,0x3f,_END_,
 
  };
 
 BYTE code tSTRING_AUDIO_SOURCE[] =
 {
	 _A_, _U_, _D_, _I_, _O_, ___, _S_, _O_, _U_, _R_, _C_, _E_, _END_,
	_S_, _O_, _U_, _R_, _C_, _E_, ___, _A_, _U_, _D_, _I_, _O_,  _END_,
   _A_, _U_, _D_, _I_, _O_, _Q_, _U_, _E_, _L_, _L_, _E_, _END_,
	_F_, _U_, _E_, _N_, _T_, _E_, ___, _A_, _U_, _D_, _I_, _O_, _END_,
	_O_, _R_, _I_, _G_, _I_, _N_, _E_, ___, _A_, _U_, _D_, _I_, _O_, _END_,
	_A_, _U_, _D_, _I_, _O_, _SLINE_, _B_, _R_, _O_, _N_, _END_,
   0x14,0x00,0x15,0x00,0x14,0x00, 0x40,0x00,0x42,_END_,
		0x3f,0x00,0x40,0x00,0x43,_END_,
	  0x3f,0x00,0x40,0x00,0x43,_END_,
 
  };
 BYTE code tSTRING_RESET[] =
 {
	 _R_, _e_, _s_, _e_, _t_, _END_,
	_R_, _e1_, _I_, _N_, _I_, _T_, _DOWNDOT_, _END_, 
	_R_, _u1_, _C_, _K_, _S_, _E_, _T_, _Z_, _E_, _N_, _END_,
	_R_, _E_, _S_, _T_, _A_, _B_, _L_, _E_, _C_, _E_, _R_, _END_,
	_R_, _I_, _P_, _R_, _I_, _S_, _T_, _I_, _N_, _O_, _END_,
	 _R_, _E_, _S_, _E_, _T_, _T_, _E_, _N_, _END_,
	0x48,0x00,0x49,0x00,0x2f,_END_,
	 0x4d,0x00,0x1a,_END_,
  0x4d,0x00,0x1a,_END_,
 
  };
 
 BYTE code tSTRING_MENU_TIME[] =
 {	 
	 _O_, _S_, _D_, ___, _T_, _i_, _m_, _e_,___,_O_,_u_, _t_, _END_,
	  _D_, _U_, _R_, _e1_, _E_, ___, _O_, _S_, _D_, _END_,	   
	  _O_, _S_, _D_, _SLINE_, _A_, _U_, _S_, _Z_, _E_, _I_, _T_, _END_,
	  _T_, _I_, _E_, _M_, _P_, _O_, ___, _D_, _E_, ___, _M_, _E_, _N_,	_U0_,_END_,
	  _T_, _E_, _M_, _P_, _O_, ___, _M_, _E_, _N_, _U_, _END_,
	  _M_, _E_, _N_, _U_, ___, _T_, _I_, _J_, _D_, _END_,
	  0x39,0x00,0x45,0x00,0x0e,0x00,0x46,_END_,
		  0x11,0x00,0x12,0x00, 0x1d,0x00,0x4a,_END_,
	 0x11,0x00,0x12,0x00, 0x1d,0x00,0x4a,_END_,
 
  };
 
 BYTE code tSTRING_OSD_HPOS[] =
 {
	  _H_, _o_, _r_, _i_, _z_, _o_, _n_, _t_, _a_, _l_, _END_,
	 _P_, _O_, _S_, _I_, _T_, _I_, _O_, _N_, _SLINE_, _H_, ___, _O_, _S_, _D_, _END_,  
	 _O_, _S_, _D_,___, _H_,_SLINE_, _P_, _O_, _S_, _I_, _T_, _I_, _O_, _N_,_END_, 
	  _P_, _O_, _S_, _DOWNDOT_,_H_, ___, _D_, _E_, ___, _O_, _S_, _D_,_END_,
	 _P_, _O_, _S_, _DOWNDOT_,_O_, _R_, _DOWNDOT_, _O_, _S_, _D_, _END_,
	  _O_, _S_, _D_, ___, _H_, _SLINE_, _P_, _O_, _S_, _I_, _T_, _I_, _E_, _END_,
	 0x66,0x67,0x68,0x00,0x1f,0x00,0x20,0x00, 0x21,0x00,0x22,_END_,
		 0x48,0x00,0x49,0x00, 0x17,0x00,0x18,0x00,0x19,0x00,0x1a,_END_,
	 0x48,0x00,0x49,0x00, 0x17,0x00,0x18,0x00,0x19,0x00,0x1a,_END_,
 
 };
 
 BYTE code tSTRING_OSD_VPOS[] =
 {
	  _V_, _e_, _r_, _t_, _i_, _c_, _a_, _l_, _END_,
	 _P_, _O_, _S_, _I_, _T_, _I_, _O_, _N_, _SLINE_, _V_, ___, _O_, _S_, _D_, _END_,  
	 _O_, _S_, _D_,___, _V_,_SLINE_, _P_, _O_, _S_, _I_, _T_, _I_, _O_, _N_,_END_,
	 _P_, _O_, _S_, _DOWNDOT_, _V_, ___, _D_, _E_, ___, _O_, _S_, _D_, _END_,
	  _P_, _O_, _S_, _DOWNDOT_, _V_, _E_, _R_, _DOWNDOT_,  _O_, _S_, _D_,_END_,
	  _O_, _S_, _D_, ___, _V_, _SLINE_, _P_, _O_, _S_, _I_, _T_, _I_, _E_, _END_,
	 0x66,0x67,0x68,0x00,0x1f,0x00,0x23,0x00, 0x21,0x00,0x22,_END_,
		 0x48,0x00,0x49, 0x00,0x1b,0x00,0x1c,0x00,0x19,0x00,0x1a,_END_,
	 0x48,0x00,0x49, 0x00,0x1b,0x00,0x1c,0x00,0x19,0x00,0x1a,_END_,
 
 };
 
 BYTE code _tSTRING_OSDSET_LANGUAGE[] =
 {
	 _L_, _a_, _n_, _g_, _u_, _a_, _g_, _e_, _END_,
	 _I_, _d_, _i_, _o_, _m_, _a_, _END_, 
	 _L_, _a_, _n_, _g_, _u_, _e_, _END_,
	 _S_, _p_, _r_, _a_, _c_, _h_, _e_, _END_,
	 _L_, _i_, _g_, _u_, _a_,  _END_,
	 _T_, _a_, _a_, _l_, _END_,
	 _EU_0x70,0x3A,0x3B,0x64, _END_, // Russia (��٬���)
	 0x3d,0x00,0x3e,_END_,
	 0x49,0x00,0x4a,_END_,//
 
  };
 
 BYTE code tCHOOSE_LANGUAGE[] =
 {
	 _E_, _n_, _g_, _l_, _i_, _s_, _h_, _END_,
	 _E_, _s_, _p_, _a_, _N0_, _o_, _l_,_END_, 
	 _F_, _r_, _a_, _n_, _c0_, _a_, _i_, _s_, _END_,
	 _D_, _e_, _u_, _t_, _s_, _c_,_h_,_END_,
	 _I_, _t_, _a_, _l_, _i_, _a_,_n_, _o_,_END_,
	 _N_, _e_, _d_, _e_, _r_, _l_,_a_, _n_, _d_, _s_, _END_,
	 0x1A, 0x63, 0x61, 0x61, 0x64, 0x65,0x66,_END_, // Russia
	 0x78,0x00,0x79,0x00,0x7a,_END_,
	 0x42,0x00,0x54,_END_,//

  };
BYTE code _tSTRING_OSDSET_HORIZONTAL[] =
 {
	  _H_, _o_, _r_, _i_, _z_, _o_, _n_, _t_, _a_, _l_, _END_,
	  _H_, _o_, _r_, _i_, _z_, _o_, _n_, _t_, _a_, _l_, _END_,
	  _H_, _o_, _r_, _i_, _z_, _o_, _n_, _t_, _a_, _l_,_e_, _END_,
	  _H_, _o_, _r_, _i_, _z_, _o_, _n_, _t_, _a_, _l_, _END_,
	  _O_, _r_, _i_, _z_, _z_, _o_, _n_, _t_, _a_, _l_,_e_, _END_,
	  _H_, _o_, _r_, _i_, _z_, _o_, _n_, _t_, _a_,_a_,_l_, _END_,
	  _EU_0x57,0x5E,0x5F,0x65,0x3A,0x5E,0x53,0x27,0x61,0x45,0x3C,0x53,0x3B,0x66,_END_, // Russia (�Ԭ��ڬ٬�߬�Ѭݬ�߬���)
	  0x3f,0x00,0x40,0x00, 0x41,0x00,0x42,_END_,
	  0x4b,0x00,0x4c,0x00, 0x4d,0x00,0x2e,_END_,//

 
 };
 
 BYTE code _tSTRING_OSDSET_VERTICAL[] =
 {
	  _V_, _e_, _r_, _t_, _i_, _c_, _a_, _l_, _END_,
	  _V_, _e_, _r_, _t_, _i_, _c_, _a_, _l_, _END_,
	  _V_, _e_, _r_, _t_, _i_, _c_, _a_, _l_,_e_, _END_,
	  _V_, _e_, _r_, _t_, _i_, _k_, _a_, _l_, _END_,
	  _V_, _e_, _r_, _t_, _i_, _c_, _a_, _l_,_e_, _END_,
	  _V_, _e_, _r_, _t_, _i_, _c_, _a_, _a_, _l_, _END_,
	  0x0C,0x62,0x5F,0x27,0x65,0x64,0x61,0x45,0x3C,_END_, // Russia (B�֬��ڬܬѬݬ�)
	  0x43,0x00,0x44,0x00, 0x41,0x00,0x46,_END_,
	  0x4e,0x00,0x4f,0x00, 0x4d,0x00,0x2e,_END_,//

 }; 
 
 BYTE code _tSTRING_OSDSET_TRANSPARENCY[] =
 {
	 _T_, _r_, _a_, _n_, _s_, _p_, _a_, _r_, _e_, _n_, _c_, _y_, _END_,
	 _T_, _r_, _a_, _n_, _s_, _p_, _a_, _r_, _e_, _n_, _c_, _i_, _a_, _END_,
	 _T_, _r_, _a_, _n_, _s_, _p_, _a_, _r_, _e_, _n_, _t_, _END_,
	 _T_, _r_, _a_, _n_, _s_, _p_, _a_, _r_, _e_, _n_, _z_, _END_,
	 _T_, _r_, _a_, _s_, _p_, _a_, _r_, _e_, _n_, _z_,_a_, _END_,
	 _D_, _o_, _o_, _r_, _z_, _i_, _c_, _h_, _t_, _i_, _g_, _h_,_e_, _i_, _d_, _END_,
	 _EU_0x5A,0x5F,0x5E,0x54,0x5F,0x61,0x40,0x53,0x5E,0x60,0x27,0x3C,_END_, // Russia - 0x3A -> 0x54
	 0x47,0x00,0x48,0x00, 0x49,_END_,
	 0x50,0x00,0x51,0x00,0x32,_END_,//
 
  };
 BYTE code _tSTRING_OSDSET_OSDTIMEOUT[] =
 {	 
	 _O_, _S_, _D_, ___, _T_, _i_, _m_, _e_,___,_O_,_u_, _t_, _END_,
	 _A_, _p_, _a_,_g_, _a_, _d_, _o_,___,_O_, _S_, _D_, _END_,
	 _O_, _S_, _D_, ___, _T_, _e_, _m_, _p_, _s_,___,_m_,_o_,_r_, _t_, _END_,
	 _O_, _S_, _D_, ___, _Z_, _e_, _i_, _t_, _a_,_b_,_l_,_a_, _u_,_f_, _END_,
     _T_, _i_, _m_, _e_,___,_O_,_u_, _t_, ___,_O_, _S_, _D_,  _END_,
	 _S_, _l_, _u_, _i_, _m_, _e_, _r_, _t_, _i_, _j_, _d_, ___, _O_, _S_, _D_, _END_,
	 0x19,0x1D,0x0E,0x00,0x0C,0x5F,0x62,0x5C,0x5D, _END_, 
	 0x4a,0x00,0x4b,0x00,0x4c,_END_,
	 0x19,0x1d,0x0e,0x00,0x9f,0x00,0xa0,0x00,0x52,0x00,0x53,_END_,//
 
  }; 
 BYTE code _tSTRING_OSDSET_ROTATE[] =
 {
	 _O_, _S_, _D_, _, _R_, _o_, _t_, _a_, _t_, _e_, _END_,
	 _O_, _S_, _D_, _, _R_, _o_, _t_, _a_, _t_, _e_, _END_,
	 _O_, _S_, _D_, _, _R_, _o_, _t_, _a_, _t_, _e_, _END_,
	 _O_, _S_, _D_, _, _R_, _o_, _t_, _a_, _t_, _e_, _END_,
	 _O_, _S_, _D_, _, _R_, _o_, _t_, _a_, _t_, _e_, _END_,
	 _O_, _S_, _D_, _, _D_, _r_, _a_, _a_, _i_, _e_, _n_, _END_,
	 _O_, _S_, _D_, _, 0x43,0x5F,0x61,0x3D,0x61,0x27,0x3C,_END_, //Russia (�Ӭ�Ѭ�Ѭ��)
	 _O_, _S_, _D_, _, _R_, _o_, _t_, _a_, _t_, _e_, _END_,
	 0x82,0x00,0x83,0x00,0x2b,0x00,0x2c,0x00,0x84,0x00,0x85,_END_,//

 };
   BYTE code _tSTRING_SETUP_INPUT[] =
  {
	 _I_, _n_, _p_, _u_, _t_, _END_,
	 _E_, _n_, _t_, _r_, _a_, _d_,_a_,  _END_, 
	 _E_, _n_, _t_, _r_, _e2_, _e_,  _END_, 
	 _E_, _i_,  _n_, _g_, _a_, _n_, _g_,  _END_, 
	 _I_, _n_, _g_, _r_, _a_, _s_, _s_,_o_, _END_,
	 _I_, _n_, _v_, _o_, _e_, _r_, _END_,
	 _EU_0x43,0x43,0x5E,0x56,_END_, //Russia (�Ӭ���)
	 0x4d,0x00,0x4e,0x00,0x4f,0x00,0x50,_END_,
	 0x55,0x00,0x56,_END_,//
 
   };
BYTE code _tSTRING_SETUP_AUDIOMUTE[] =
{
	_M_, _u_, _t_, _e_,  _END_,
	_M_, _u_, _t_, _e_,  _END_,
	_M_, _u_, _t_, _e_,  _END_,
	_M_, _u_, _t_, _e_,  _END_,
	_M_, _u_, _t_, _e_,  _END_,
	_D_, _e_, _m_, _p_, _t_, _END_,
	_EU_0x5A,0x5F,0x65,0x58,0x45,0x63,0x3D,0x61,0x62,0x27,_END_, // Russia (���ڬԬݬ��Ѭ֬�)
    0x2a,0x00,0x30,0x00,0x52,_END_,
    0x57,0x00,0x58,_END_,//


};
 BYTE code _tSTRING_SETUP_AUDIO[] =
{
	 _V_, _o_, _l_, _u_, _m_, _e_, _END_, 
	 _V_, _o_, _l_, _u_, _m_, _e_, _END_, 
	 _V_, _o_, _l_, _u_, _m_, _e_, _END_, 
	 _V_, _o_, _l_, _u_, _m_, _e_, _END_, 
	 _V_, _o_, _l_, _u_, _m_, _e_, _END_, 
	 _V_, _o_, _l_, _u_, _m_, _e_, _END_,
	 _EU_0x57,0x5F,0x5E,0x5C,0x64,0x5E,0x60,0x27,0x3C,_END_, // Russia (�����ެܬ����)
	 0x2a,0x00,0x6a,_END_,
	 0x58,0x00,0x80,_END_,//
 };

   
 BYTE code _tSTRING_SETUP_RESET[] =
 {
	 _R_, _e_, _s_, _e_, _t_, _END_,
	 _R_, _e_, _i_, _n_, _i_, _c_,_i_, _o_, _DOWNDOT_, _END_, 
	 _R_, _e2_, _i_, _n_, _i_, _t_,_DOT_, _END_, 
	 _Z_, _u_, _r_, _U0_, _c_, _k_, _s_, _e_, _t_, _z_, _e_,_n_, _END_,
	 _R_, _e_, _s_, _e_, _t_, _END_,
	 _R_, _e_, _s_, _e_, _t_, _END_,
	 _EU_0x60,0x4A,0x5F,0x5E,0x60,_END_, // Russia (��Ҭ���)
	0x51,0x00,0x2d,0x00,0x53,_END_,
	0xa3,0x00,0x2e,_END_, //
  };
  BYTE code _tSTRING_SETUP_DVI[] =
  {
	  _D_, _V_, _I_, _END_,
	  _D_, _V_, _I_, _END_,
	 _R_, _u1_, _C_, _K_, _S_, _E_, _T_, _Z_, _E_, _N_, _END_,
	 _R_, _E_, _S_, _T_, _A_, _B_, _L_, _E_, _C_, _E_, _R_, _END_,
	 _R_, _I_, _P_, _R_, _I_, _S_, _T_, _I_, _N_, _O_, _END_,
	  _R_, _E_, _S_, _E_, _T_, _T_, _E_, _N_, _END_,
	 0x48,0x00,0x49,0x00,0x2f,_END_,
	  0x0e,0x20,0x13,_END_,
		  0x0e,0x20,0x13,_END_,
  
   };

  BYTE code _tSTRING_SETUP_HDMI[] =
  {
	  _H_, _D_, _M_, _I_, _END_,
	  _H_, _D_, _M_, _I_, _END_,
	 _R_, _u1_, _C_, _K_, _S_, _E_, _T_, _Z_, _E_, _N_, _END_,
	 _R_, _E_, _S_, _T_, _A_, _B_, _L_, _E_, _C_, _E_, _R_, _END_,
	 _R_, _I_, _P_, _R_, _I_, _S_, _T_, _I_, _N_, _O_, _END_,
	  _R_, _E_, _S_, _E_, _T_, _T_, _E_, _N_, _END_,
	 0x48,0x00,0x49,0x00,0x2f,_END_,
		  0x12,0x0e,0x17,0x13,_END_,
		  0x12,0x0e,0x17,0x13,_END_,
  
   };
  BYTE code _tSTRING_SETUP_DP[] =
  {
	  _D_, _P_,_END_,
	  _D_, _P_,_END_,
	  _D_, _P_,_END_,
	 _R_, _E_, _S_, _T_, _A_, _B_, _L_, _E_, _C_, _E_, _R_, _END_,
	 _R_, _I_, _P_, _R_, _I_, _S_, _T_, _I_, _N_, _O_, _END_,
	  _R_, _E_, _S_, _E_, _T_, _T_, _E_, _N_, _END_,
	 0x48,0x00,0x49,0x00,0x2f,_END_,
	  0x0e,0x1a,_END_,
		  0x0e,0x1a,_END_,
  
   };
  BYTE code _tSTRING_SETUP_VGA[] =
  {
	  _V_, _G_,_A_,_END_,
	  _V_, _G_,_A_,_END_,
	  _V_, _G_,_A_,_END_,
	  _V_, _G_,_A_,_END_,
	  _V_, _G_,_A_,_END_,
	  _V_, _G_,_A_,_END_,
	  _V_, _G_,_A_,_END_,
	  _V_, _G_,_A_,_END_,
	  _V_, _G_,_A_,_END_,
  
   };
  BYTE code _tSTRING_OUT_OF_RANGE[] =
  {
	   _O_, _U_,_T_,_, _O_, _F_,_, _R_, _A_, _N_, _G_, _E_,_END_,
  
   };

  
  BYTE code _tSTRING_NO_VIDEO_INPUT[] =
  {
	   _N_, _O_, _, _V_, _I_, _D_,  _E_, _O_, _, _I_, _N_, _P_, _U_, _T_,_END_,
	 _R_, _e1_, _I_, _N_, _I_, _T_, _DOWNDOT_, _END_, 
	 _R_, _u1_, _C_, _K_, _S_, _E_, _T_, _Z_, _E_, _N_, _END_,
	 _R_, _E_, _S_, _T_, _A_, _B_, _L_, _E_, _C_, _E_, _R_, _END_,
	 _R_, _I_, _P_, _R_, _I_, _S_, _T_, _I_, _N_, _O_, _END_,
	  _R_, _E_, _S_, _E_, _T_, _T_, _E_, _N_, _END_,
	 0x48,0x00,0x49,0x00,0x2f,_END_,
	  0x0e,0x1a,_END_,
		  0x0e,0x1a,_END_,
  
   };

BYTE code _tSTRING_STANDBY_MODE[] =
{
	 _S_, _T_,  _A_, _N_, _D_,  _B_, _Y_, _, _M_, _O_, _D_, _E_,_END_,
	 _S_, _T_,	_A_, _N_, _D_,	_B_, _Y_, _, _M_, _O_, _D_, _E_,_END_,
	 _S_, _T_,	_A_, _N_, _D_,	_B_, _Y_, _, _M_, _O_, _D_, _E_,_END_,
	 _S_, _T_,	_A_, _N_, _D_,	_B_, _Y_, _, _M_, _O_, _D_, _E_,_END_,
	 _S_, _T_,	_A_, _N_, _D_,	_B_, _Y_, _, _M_, _O_, _D_, _E_,_END_,
	_R_, _E_, _S_, _E_, _T_, _T_, _E_, _N_, _END_,
   0x48,0x00,0x49,0x00,0x2f,_END_,
	0x0e,0x1a,_END_,
		0x0e,0x1a,_END_,

 };

BYTE code _tSTRING_NO_SIGNAL[] =
{
	 _N_, _O_, _, _S_, _I_, _G_,  _N_, _A_, _L_,_, _I_, _N_, _P_, _U_, _T_,_END_,
	 _N_, _O_, _, _S_, _I_, _G_,  _N_, _A_, _L_,_, _I_, _N_, _P_, _U_, _T_,_END_,
	 _N_, _O_, _, _S_, _I_, _G_,  _N_, _A_, _L_,_, _I_, _N_, _P_, _U_, _T_,_END_,
	 _N_, _O_, _, _S_, _I_, _G_,  _N_, _A_, _L_,_, _I_, _N_, _P_, _U_, _T_,_END_,
	 _N_, _O_, _, _S_, _I_, _G_,  _N_, _A_, _L_,_, _I_, _N_, _P_, _U_, _T_,_END_,
	_R_, _E_, _S_, _E_, _T_, _T_, _E_, _N_, _END_,
   0x48,0x00,0x49,0x00,0x2f,_END_,
	0x0e,0x1a,_END_,
		0x0e,0x1a,_END_,
 };

BYTE code _tSTRING_OTHER_ALCW_SETTING[] =
{
	 _A_,_L_,_C_,_W_,_END_,
	 _A_,_L_,_C_,_W_,_END_,
	 _A_,_L_,_C_,_W_,_END_,
	 _A_,_L_,_C_,_W_,_END_,
	 _A_,_L_,_C_,_W_,_END_,
	 _A_,_L_,_C_,_W_,_END_,
	 _A_,_L_,_C_,_W_,_END_, // Russia
	 _A_,_L_,_C_,_W_,_END_,
	 _A_,_L_,_C_,_W_,_END_,
};


BYTE code _tSTRING_OTHER_VIDEO_WALL_SETTINGS[] =
{
	 _V_,_i_,_d_,_e_, _o_, _, _W_, _a_, _l_, _l_, _, _S_, _e_, _t_, _t_, _i_, _n_, _g_, _s_, _END_,
	 _V_,_i_,_d_,_e_, _o_, _, _W_, _a_, _l_, _l_, _, _S_, _e_, _t_, _t_, _i_, _n_, _g_, _s_, _END_,
	 _V_,_i_,_d_,_e_, _o_, _, _W_, _a_, _l_, _l_, _, _S_, _e_, _t_, _t_, _i_, _n_, _g_, _s_, _END_,
	 _V_,_i_,_d_,_e_, _o_, _, _W_, _a_, _l_, _l_, _, _S_, _e_, _t_, _t_, _i_, _n_, _g_, _s_, _END_,
	 _V_,_i_,_d_,_e_, _o_, _, _W_, _a_, _l_, _l_, _, _S_, _e_, _t_, _t_, _i_, _n_, _g_, _s_, _END_,
	 _V_,_i_,_d_,_e_, _o_, _, _W_, _a_, _l_, _l_, _, _S_, _e_, _t_, _t_, _i_, _n_, _g_, _s_, _END_,
	 _V_,_I_,_D_,_E_, _O_, _, _W_, _A_, _L_, _L_, _, _S_, _E_, _T_, _T_, _I_, _N_, _G_, _S_, _END_, // Russia
	 _V_,_i_,_d_,_e_, _o_, _, _W_, _a_, _l_, _l_, _, _S_, _e_, _t_, _t_, _i_, _n_, _g_, _s_, _END_,
	 0x90,0x00,0x91,0x00,0x92,0x00,0x2d,0x00,0x2e, _END_,//
};
#if (_ENABLE_VIDEO_WALL == _ON)
BYTE code _tSTRING_OTHER_VIDEO_WALL[] =
{
	 _V_,_i_,_d_,_e_, _o_, _, _W_, _a_, _l_, _l_, _END_,
	 _V_,_i_,_d_,_e_, _o_, _, _W_, _a_, _l_, _l_, _END_,
	 _V_,_i_,_d_,_e_, _o_, _, _W_, _a_, _l_, _l_, _END_,
	 _V_,_i_,_d_,_e_, _o_, _, _W_, _a_, _l_, _l_, _END_,
	 _V_,_i_,_d_,_e_, _o_, _, _W_, _a_, _l_, _l_, _END_,
	 _V_,_i_,_d_,_e_, _o_, _, _W_, _a_, _l_, _l_, _END_,
	 _V_,_I_,_D_,_E_, _O_, _, _W_, _A_, _L_, _L_, _END_, // Russia
	 _V_,_i_,_d_,_e_, _o_, _, _W_, _a_, _l_, _l_, _END_,
	 0x90,0x00,0x91,0x00,0x92, _END_,//
};

BYTE code _tSTRING_OTHER_DISPLAY_NUMBER[] =
{
	 _D_, _i_, _s_, _p_, _l_, _a_, _y_, _, _N_, _u_, _m_, _b_, _e_, _r_, _END_,
	 _D_, _i_, _s_, _p_, _l_, _a_, _y_, _, _N_, _u_, _m_, _b_, _e_, _r_, _END_,
	 _D_, _i_, _s_, _p_, _l_, _a_, _y_, _, _N_, _u_, _m_, _b_, _e_, _r_, _END_,
	 _D_, _i_, _s_, _p_, _l_, _a_, _y_, _, _N_, _u_, _m_, _b_, _e_, _r_, _END_,
	 _D_, _i_, _s_, _p_, _l_, _a_, _y_, _, _N_, _u_, _m_, _b_, _e_, _r_, _END_,
	 _D_, _i_, _s_, _p_, _l_, _a_, _y_, _, _N_, _u_, _m_, _b_, _e_, _r_, _END_,
	 _D_, _I_, _S_, _P_, _L_, _A_, _Y_, _, _N_, _U_, _M_, _B_, _E_, _R_, _END_, // Russia
	 _D_, _i_, _s_, _p_, _l_, _a_, _y_, _, _N_, _u_, _m_, _b_, _e_, _r_, _END_,
	 0x82,0x00,0x83,0x00,0x8e,_END_,//
};

BYTE code _tSTRING_OTHER_HORIZONTAL_NUMBER[] =
{
	 _H_, _o_, _r_, _i_, _z_, _o_, _n_, _t_, _a_, _l_, _, _N_, _u_, _m_, _b_, _e_, _r_, _END_,
	 _H_, _o_, _r_, _i_, _z_, _o_, _n_, _t_, _a_, _l_, _, _N_, _u_, _m_, _b_, _e_, _r_, _END_,
	 _H_, _o_, _r_, _i_, _z_, _o_, _n_, _t_, _a_, _l_, _, _N_, _u_, _m_, _b_, _e_, _r_, _END_,
	 _H_, _o_, _r_, _i_, _z_, _o_, _n_, _t_, _a_, _l_, _, _N_, _u_, _m_, _b_, _e_, _r_, _END_,
	 _H_, _o_, _r_, _i_, _z_, _o_, _n_, _t_, _a_, _l_, _, _N_, _u_, _m_, _b_, _e_, _r_, _END_,
	 _H_, _o_, _r_, _i_, _z_, _o_, _n_, _t_, _a_, _l_, _, _N_, _u_, _m_, _b_, _e_, _r_, _END_,
	 _H_, _O_, _R_, _I_, _Z_, _O_, _N_, _T_, _A_, _L_, _, _N_, _U_, _M_, _B_, _E_, _R_, _END_, // Russia
	 _H_, _o_, _r_, _i_, _z_, _o_, _n_, _t_, _a_, _l_, _, _N_, _u_, _m_, _b_, _e_, _r_, _END_,
	 0x4b,0x00,0x4c,0x00,0x82,0x00,0x83,0x00,0x8e,_END_, //
};

BYTE code _tSTRING_OTHER_VERTICAL_NUMBER[] =
{
	 _V_, _e_, _r_, _t_, _i_, _c_, _a_, _l_, _, _N_, _u_, _m_, _b_, _e_, _r_, _END_,
	 _V_, _e_, _r_, _t_, _i_, _c_, _a_, _l_, _, _N_, _u_, _m_, _b_, _e_, _r_, _END_,
	 _V_, _e_, _r_, _t_, _i_, _c_, _a_, _l_, _, _N_, _u_, _m_, _b_, _e_, _r_, _END_,
	 _V_, _e_, _r_, _t_, _i_, _c_, _a_, _l_, _, _N_, _u_, _m_, _b_, _e_, _r_, _END_,
	 _V_, _e_, _r_, _t_, _i_, _c_, _a_, _l_, _, _N_, _u_, _m_, _b_, _e_, _r_, _END_,
	 _V_, _e_, _r_, _t_, _i_, _c_, _a_, _l_, _, _N_, _u_, _m_, _b_, _e_, _r_, _END_,
	 _V_, _E_, _R_, _T_, _I_, _C_, _A_, _L_, _, _N_, _U_, _M_, _B_, _E_, _R_, _END_, // Russia
	 _V_, _e_, _r_, _t_, _i_, _c_, _a_, _l_, _, _N_, _u_, _m_, _b_, _e_, _r_, _END_,
	 0x4e,0x00,0x82,0x00,0x83,0x00,0x4f,0x00,0x8e,_END_,//
};

BYTE code _tSTRING_OTHER_RS232_ID[] =
{
	_R_, _S_, _2_, _3_, _2_, _, _I_, _D_, _END_,
	_R_, _S_, _2_, _3_, _2_, _, _I_, _D_, _END_,
	_R_, _S_, _2_, _3_, _2_, _, _I_, _D_, _END_,
	_R_, _S_, _2_, _3_, _2_, _, _I_, _D_, _END_,
	_R_, _S_, _2_, _3_, _2_, _, _I_, _D_, _END_,
	_R_, _S_, _2_, _3_, _2_, _, _I_, _D_, _END_,
	_R_, _S_, _2_, _3_, _2_, _, _I_, _D_, _END_, // Russia
	_R_, _S_, _2_, _3_, _2_, _, _I_, _D_, _END_,
	_R_, _S_, _2_, _3_, _2_, _, _I_, _D_, _END_,//
};
#endif


BYTE code _tSTRING_LIGHT_SENSOR[] =
{
	_L_, _i_, _g_, _h_, _t_, _, _S_, _e_, _n_, _s_, _o_, _r_, _END_,
	_L_, _i_, _g_, _h_, _t_, _, _S_, _e_, _n_, _s_, _o_, _r_, _END_,
	_L_, _i_, _g_, _h_, _t_, _, _S_, _e_, _n_, _s_, _o_, _r_, _END_,
	_L_, _i_, _g_, _h_, _t_, _, _S_, _e_, _n_, _s_, _o_, _r_, _END_,
	_L_, _i_, _g_, _h_, _t_, _, _S_, _e_, _n_, _s_, _o_, _r_, _END_,
	_L_, _i_, _g_, _h_, _t_, _, _S_, _e_, _n_, _s_, _o_, _r_, _END_,
	_L_, _I_, _G_, _H_, _T_, _, _S_, _E_, _N_, _S_, _O_, _R_, _END_, // Russia
	_L_, _i_, _g_, _h_, _t_, _, _S_, _e_, _n_, _s_, _o_, _r_, _END_,
	0x93,0x00,0x94,0x00,0x95,0x00,0x96,_END_,//
};



BYTE code _tSTRING_OTHER_FAN_CONTROLS[] =
{
	_F_, _a_, _n_, ___, _C_, _o_, _n_, _t_, _r_, _o_, _l_, _s_,_END_,
	_F_, _a_, _n_, ___, _C_, _o_, _n_, _t_, _r_, _o_, _l_, _s_,_END_,
	_F_, _a_, _n_, ___, _C_, _o_, _n_, _t_, _r_, _o_, _l_, _s_,_END_,
	_F_, _a_, _n_, ___, _C_, _o_, _n_, _t_, _r_, _o_, _l_, _s_,_END_,
	_F_, _a_, _n_, ___, _C_, _o_, _n_, _t_, _r_, _o_, _l_, _s_,_END_,
	_F_, _a_, _n_, ___, _C_, _o_, _n_, _t_, _r_, _o_, _l_, _s_,_END_,
	_F_, _A_, _N_, ___, _C_, _O_, _N_, _T_, _R_, _O_, _L_, _S_,_END_, // Russia
	_F_, _a_, _n_, ___, _C_, _o_, _n_, _t_, _r_, _o_, _l_, _s_,_END_,
	0x97,0x00,0x98,0x00,0x2d,0x00,0x2e,_END_,//
};
#if (_ENABLE_FAN_CONTROL == _ON)
BYTE code _tSTRING_OTHER_FAN[] =
{
	_F_, _a_, _n_, ___, _S_, _t_, _a_, _t_, _u_, _s_, _END_,
	_F_, _a_, _n_, ___, _S_, _t_, _a_, _t_, _u_, _s_, _END_,
	_F_, _a_, _n_, ___, _S_, _t_, _a_, _t_, _u_, _s_, _END_,
	_F_, _a_, _n_, ___, _S_, _t_, _a_, _t_, _u_, _s_, _END_,
	_F_, _a_, _n_, ___, _S_, _t_, _a_, _t_, _u_, _s_, _END_,
	_F_, _a_, _n_, ___, _S_, _t_, _a_, _t_, _u_, _s_, _END_,
	_F_, _A_, _N_, ___, _S_, _T_, _A_, _T_, _U_, _S_, _END_, // Russia
	_F_, _a_, _n_, ___, _S_, _t_, _a_, _t_, _u_, _s_, _END_,
	0x97,0x00,0x98,0x00,0x99,0x00,0x9a, _END_,//
};

BYTE code _tSTRING_OTHER_FAN_PWM1[] =
{
	_F_, _a_, _n_, ___, _P_, _W_, _M_, _1_, _END_,
	_F_, _a_, _n_, ___, _P_, _W_, _M_, _1_, _END_,
	_F_, _a_, _n_, ___, _P_, _W_, _M_, _1_, _END_,
	_F_, _a_, _n_, ___, _P_, _W_, _M_, _1_, _END_,
	_F_, _a_, _n_, ___, _P_, _W_, _M_, _1_, _END_,
	_F_, _a_, _n_, ___, _P_, _W_, _M_, _1_, _END_,
	_F_, _A_, _N_, ___, _P_, _W_, _M_, _1_, _END_, // Russia
	_F_, _a_, _n_, ___, _P_, _W_, _M_, _1_, _END_,
	0x97,0x00,0x98,0x00, _P_, _W_, _M_, _1_, _END_,//
};

BYTE code _tSTRING_OTHER_FAN_PWM2[] =
{
	_F_, _a_, _n_, ___, _P_, _W_, _M_, _2_, _END_,
	_F_, _a_, _n_, ___, _P_, _W_, _M_, _2_, _END_,
	_F_, _a_, _n_, ___, _P_, _W_, _M_, _2_, _END_,
	_F_, _a_, _n_, ___, _P_, _W_, _M_, _2_, _END_,
	_F_, _a_, _n_, ___, _P_, _W_, _M_, _2_, _END_,
	_F_, _a_, _n_, ___, _P_, _W_, _M_, _2_, _END_,
	_F_, _A_, _N_, ___, _P_, _W_, _M_, _2_, _END_, // Russia
	_F_, _a_, _n_, ___, _P_, _W_, _M_, _2_, _END_,
	0x97,0x00,0x98,0x00, _P_, _W_, _M_, _2_, _END_,//
};

BYTE code _tSTRING_OTHER_FAN_PWM3[] =
{
	_F_, _a_, _n_, ___, _P_, _W_, _M_, _3_, _END_,
	_F_, _a_, _n_, ___, _P_, _W_, _M_, _3_, _END_,
	_F_, _a_, _n_, ___, _P_, _W_, _M_, _3_, _END_,
	_F_, _a_, _n_, ___, _P_, _W_, _M_, _3_, _END_,
	_F_, _a_, _n_, ___, _P_, _W_, _M_, _3_, _END_,
	_F_, _a_, _n_, ___, _P_, _W_, _M_, _3_, _END_,
	_F_, _A_, _N_, ___, _P_, _W_, _M_, _3_, _END_, // Russia
	_F_, _a_, _n_, ___, _P_, _W_, _M_, _3_, _END_,
	0x97,0x00,0x98,0x00, _P_, _W_, _M_, _3_, _END_,//
};

BYTE code _tSTRING_OTHER_FAN_PWM4[] =
{
	_F_, _a_, _n_, ___, _P_, _W_, _M_, _4_, _END_,
	_F_, _a_, _n_, ___, _P_, _W_, _M_, _4_, _END_,
	_F_, _a_, _n_, ___, _P_, _W_, _M_, _4_, _END_,
	_F_, _a_, _n_, ___, _P_, _W_, _M_, _4_, _END_,
	_F_, _a_, _n_, ___, _P_, _W_, _M_, _4_, _END_,
	_F_, _a_, _n_, ___, _P_, _W_, _M_, _4_, _END_,
	_F_, _A_, _N_, ___, _P_, _W_, _M_, _4_, _END_, // Russia
	_F_, _a_, _n_, ___, _P_, _W_, _M_, _4_, _END_,
	0x97,0x00,0x98,0x00, _P_, _W_, _M_, _4_, _END_,//
};

BYTE code _tSTRING_OTHER_SHUTDOWN[] =
{
	_S_, _h_, _u_, _t_, _d_, _o_, _w_, _n_,_END_,
	_S_, _h_, _u_, _t_, _d_, _o_, _w_, _n_,_END_,
	_S_, _h_, _u_, _t_, _d_, _o_, _w_, _n_,_END_,
	_S_, _h_, _u_, _t_, _d_, _o_, _w_, _n_,_END_,
	_S_, _h_, _u_, _t_, _d_, _o_, _w_, _n_,_END_,
	_S_, _h_, _u_, _t_, _d_, _o_, _w_, _n_,_END_,
	_S_, _H_, _U_, _T_, _D_, _O_, _W_, _N_,_END_, // Russia
	_S_, _h_, _u_, _t_, _d_, _o_, _w_, _n_,_END_,
	0x40,0x00,0x8f,_END_,//
};

BYTE code _tSTRING_OTHER_SHUTDOWN_TEMP[] =
{
	_S_, _h_, _u_, _t_, _d_, _o_, _w_, _n_, ___, _T_, _e_, _m_, _p_,_END_,
	_S_, _h_, _u_, _t_, _d_, _o_, _w_, _n_, ___, _T_, _e_, _m_, _p_,_END_,
	_S_, _h_, _u_, _t_, _d_, _o_, _w_, _n_, ___, _T_, _e_, _m_, _p_,_END_,
	_S_, _h_, _u_, _t_, _d_, _o_, _w_, _n_, ___, _T_, _e_, _m_, _p_,_END_,
	_S_, _h_, _u_, _t_, _d_, _o_, _w_, _n_, ___, _T_, _e_, _m_, _p_,_END_,
	_S_, _h_, _u_, _t_, _d_, _o_, _w_, _n_, ___, _T_, _e_, _m_, _p_,_END_,
	_S_, _H_, _U_, _T_, _D_, _O_, _W_, _N_, ___, _T_, _E_, _M_, _P_,_END_, // Russia
	_S_, _h_, _u_, _t_, _d_, _o_, _w_, _n_, ___, _T_, _e_, _m_, _p_,_END_,
	0x40,0x00,0x8f,0x00,0x45,0x00,0x32,_END_,//
};

BYTE code _tSTRING_OTHER_TEMP[] =
{
	_T_, _e_, _m_, _p_, _e_, _r_, _a_, _t_, _u_, _r_, _e_,_END_,
	_T_, _e_, _m_, _p_, _e_, _r_, _a_, _t_, _u_, _r_, _e_,_END_,
	_T_, _e_, _m_, _p_, _e_, _r_, _a_, _t_, _u_, _r_, _e_,_END_,
	_T_, _e_, _m_, _p_, _e_, _r_, _a_, _t_, _u_, _r_, _e_,_END_,
	_T_, _e_, _m_, _p_, _e_, _r_, _a_, _t_, _u_, _r_, _e_,_END_,
	_T_, _e_, _m_, _p_, _e_, _r_, _a_, _t_, _u_, _r_, _e_,_END_,
	_T_, _E_, _M_, _P_, _E_, _R_, _A_, _T_, _U_, _R_, _E_,_END_, // Russia
	_T_, _e_, _m_, _p_, _e_, _r_, _a_, _t_, _u_, _r_, _e_,_END_,
	0x45,0x00,0x32,_END_,
};

BYTE code _tSTRING_OTHER_TEMP1[] =
{
	_T_, _e_, _m_, _p_, _1_,_END_,
	_T_, _e_, _m_, _p_, _1_,_END_,
	_T_, _e_, _m_, _p_, _1_,_END_,
	_T_, _e_, _m_, _p_, _1_,_END_,
	_T_, _e_, _m_, _p_, _1_,_END_,
	_T_, _e_, _m_, _p_, _1_,_END_,
	_T_, _E_, _M_, _P_, _1_,_END_, // Russia
	_T_, _e_, _m_, _p_, _1_,_END_,
	0x45,0x00,0x32,0x00,_1_,_END_,
};

BYTE code _tSTRING_OTHER_TEMP2[] =
{
	_T_, _e_, _m_, _p_, _2_,_END_,
	_T_, _e_, _m_, _p_, _2_,_END_,
	_T_, _e_, _m_, _p_, _2_,_END_,
	_T_, _e_, _m_, _p_, _2_,_END_,
	_T_, _e_, _m_, _p_, _2_,_END_,
	_T_, _e_, _m_, _p_, _2_,_END_,
	_T_, _E_, _M_, _P_, _2_,_END_, // Russia
	_T_, _e_, _m_, _p_, _2_,_END_,
	0x45,0x00,0x32,0x00, _2_,_END_,
};

BYTE code _tSTRING_OTHER_TEMP3[] =
{
	_T_, _e_, _m_, _p_, _3_,_END_,
	_T_, _e_, _m_, _p_, _3_,_END_,
	_T_, _e_, _m_, _p_, _3_,_END_,
	_T_, _e_, _m_, _p_, _3_,_END_,
	_T_, _e_, _m_, _p_, _3_,_END_,
	_T_, _e_, _m_, _p_, _3_,_END_,
	_T_, _E_, _M_, _P_, _3_,_END_, // Russia
	_T_, _e_, _m_, _p_, _3_,_END_,
	0x45,0x00,0x32,0x00,_3_,_END_,
};

BYTE code _tSTRING_OTHER_TEMP4[] =
{
	_T_, _e_, _m_, _p_, _4_,_END_,
	_T_, _e_, _m_, _p_, _4_,_END_,
	_T_, _e_, _m_, _p_, _4_,_END_,
	_T_, _e_, _m_, _p_, _4_,_END_,
	_T_, _e_, _m_, _p_, _4_,_END_,
	_T_, _e_, _m_, _p_, _4_,_END_,
	_T_, _E_, _M_, _P_, _4_,_END_, // Russia
	_T_, _e_, _m_, _p_, _4_,_END_,
	0x45,0x00,0x32,0x00,_4_,_END_,
};

BYTE code _tSTRING_OTHER_TEMP5[] =
{
	_T_, _e_, _m_, _p_, _5_,_END_,
	_T_, _e_, _m_, _p_, _5_,_END_,
	_T_, _e_, _m_, _p_, _5_,_END_,
	_T_, _e_, _m_, _p_, _5_,_END_,
	_T_, _e_, _m_, _p_, _5_,_END_,
	_T_, _e_, _m_, _p_, _5_,_END_,
	_T_, _E_, _M_, _P_, _5_,_END_, // Russia
	_T_, _e_, _m_, _p_, _5_,_END_,
	0x45,0x00,0x32,0x00,_5_,_END_,
};
#endif


BYTE code _tSTRING_OTHER_SELF_CHECK[] =
{
	_S_, _e_, _l_, _f_, ___, _C_, _h_, _e_, _c_, _k_,_END_,
	_S_, _e_, _l_, _f_, ___, _C_, _h_, _e_, _c_, _k_,_END_,
	_S_, _e_, _l_, _f_, ___, _C_, _h_, _e_, _c_, _k_,_END_,
	_S_, _e_, _l_, _f_, ___, _C_, _h_, _e_, _c_, _k_,_END_,
	_S_, _e_, _l_, _f_, ___, _C_, _h_, _e_, _c_, _k_,_END_,
	_S_, _e_, _l_, _f_, ___, _C_, _h_, _e_, _c_, _k_,_END_,
	_S_, _E_, _L_, _F_, ___, _C_, _H_, _E_, _C_, _K_,_END_, // Russia
	_S_, _e_, _l_, _f_, ___, _C_, _h_, _e_, _c_, _k_,_END_,
	0x66,0x00,0x9b,0x00,0x9c,0x00,0x9d,_END_,
};

BYTE code _tSTRING_SERVICE_PWM_RES[] =
{
	_B_, _a_, _c_, _k_, _l_,_i_,_g_, _h_, _t_, _SHIFT_RIGHT_, _P_, _W_, _M_, ___,_R_,_E_,_S_,_END_,
	_B_, _a_, _c_, _k_, _l_,_i_,_g_, _h_, _t_, _SHIFT_RIGHT_, _P_, _W_, _M_, ___,_R_,_E_,_S_,_END_,
	_B_, _a_, _c_, _k_, _l_,_i_,_g_, _h_, _t_, _SHIFT_RIGHT_, _P_, _W_, _M_, ___,_R_,_E_,_S_,_END_,
	_B_, _a_, _c_, _k_, _l_,_i_,_g_, _h_, _t_, _SHIFT_RIGHT_, _P_, _W_, _M_, ___,_R_,_E_,_S_,_END_,
	_B_, _a_, _c_, _k_, _l_,_i_,_g_, _h_, _t_, _SHIFT_RIGHT_, _P_, _W_, _M_, ___,_R_,_E_,_S_,_END_,
	_B_, _a_, _c_, _k_, _l_,_i_,_g_, _h_, _t_, _SHIFT_RIGHT_, _P_, _W_, _M_, ___,_R_,_E_,_S_,_END_,
	_B_, _A_, _C_, _K_, _L_,_I_,_G_, _H_, _T_, _RIGHT_ARROWS_,_P_, _W_, _M_, ___,_R_,_E_,_S_,_END_, // Russia
	_B_, _a_, _c_, _k_, _l_,_i_,_g_, _h_, _t_, _SHIFT_RIGHT_, _P_, _W_, _M_, ___,_R_,_E_,_S_,_END_,
	0x6f,0x00,0x5f,0x00,0xa5,0x00,_P_, _W_, _M_, ___,_R_,_E_,_S_,_END_,
};

BYTE code _tSTRING_SERVICE_CONTROL[] =
{
	_SHIFT_RIGHT_,  ___,_C_,_o_,_n_,_t_,_r_,_o_,_l_,_END_,
	_SHIFT_RIGHT_,  ___,_C_,_o_,_n_,_t_,_r_,_o_,_l_,_END_,
	_SHIFT_RIGHT_,  ___,_C_,_o_,_n_,_t_,_r_,_o_,_l_,_END_,
	_SHIFT_RIGHT_,  ___,_C_,_o_,_n_,_t_,_r_,_o_,_l_,_END_,
	_SHIFT_RIGHT_,  ___,_C_,_o_,_n_,_t_,_r_,_o_,_l_,_END_,
	_SHIFT_RIGHT_,  ___,_C_,_o_,_n_,_t_,_r_,_o_,_l_,_END_,
	_RIGHT_ARROWS_, ___,_C_,_O_,_N_,_T_,_R_,_O_,_L_,_END_, // Russia
	_SHIFT_RIGHT_,  ___,_C_,_o_,_n_,_t_,_r_,_o_,_l_,_END_,
	0xa5, ___, 0x2d,0x00,0x2e,_END_,
};

#if(_PIXEL_SHIFT_SUPPORT == _ON)
BYTE code _tSTRING_SERVICE_PIXEL_SHIFT[] =
{
	_P_,_i_,_x_,_e_,_l_,___,_S_,_h_,_i_,_f_,_t_,_END_,
	_P_,_i_,_x_,_e_,_l_,___,_S_,_h_,_i_,_f_,_t_,_END_,
	_P_,_i_,_x_,_e_,_l_,___,_S_,_h_,_i_,_f_,_t_,_END_,
	_P_,_i_,_x_,_e_,_l_,___,_S_,_h_,_i_,_f_,_t_,_END_,
	_P_,_i_,_x_,_e_,_l_,___,_S_,_h_,_i_,_f_,_t_,_END_,
	_P_,_i_,_x_,_e_,_l_,___,_S_,_h_,_i_,_f_,_t_,_END_,
	_P_,_I_,_X_,_E_,_L_,___,_S_,_H_,_I_,_F_,_T_,_END_, // Russia
	_P_,_i_,_x_,_e_,_l_,___,_S_,_h_,_i_,_f_,_t_,_END_,
	_P_,_I_,_X_,_E_,_L_,___,_S_,_H_,_I_,_F_,_T_,_END_, // Russia
};

BYTE code _tSTRING_SERVICE_PIXEL_SHIFT_TIME[] =
{
	_SHIFT_RIGHT_,  ___,_T_,_i_,_m_,_e_,_END_,
	_SHIFT_RIGHT_,  ___,_T_,_i_,_m_,_e_,_END_,
	_SHIFT_RIGHT_,  ___,_T_,_i_,_m_,_e_,_END_,
	_SHIFT_RIGHT_,  ___,_T_,_i_,_m_,_e_,_END_,
	_SHIFT_RIGHT_,  ___,_T_,_i_,_m_,_e_,_END_,
	_SHIFT_RIGHT_,  ___,_T_,_i_,_m_,_e_,_END_,
	_RIGHT_ARROWS_, ___,_T_,_I_,_M_,_E_,_END_, // Russia
	_SHIFT_RIGHT_,  ___,_T_,_i_,_m_,_e_,_END_,
	0xa5, ___,_T_,_I_,_M_,_E_,_END_,
};

#endif
//BYTE code _tSTRING_SERVICE_INVERT[] =
//{
//	_SHIFT_RIGHT_,  ___,_I_,_n_,_v_,_e_,_r_,_t_,_END_,
//	_SHIFT_RIGHT_,  ___,_I_,_n_,_v_,_e_,_r_,_t_,_END_,
//	_SHIFT_RIGHT_,  ___,_I_,_n_,_v_,_e_,_r_,_t_,_END_,
//	_SHIFT_RIGHT_,  ___,_I_,_n_,_v_,_e_,_r_,_t_,_END_,
//	_SHIFT_RIGHT_,  ___,_I_,_n_,_v_,_e_,_r_,_t_,_END_,
//	_SHIFT_RIGHT_,  ___,_I_,_n_,_v_,_e_,_r_,_t_,_END_,
//	_RIGHT_ARROWS_, ___,_I_,_N_,_V_,_E_,_R_,_T_,_END_, // Russia
//	_SHIFT_RIGHT_,  ___,_I_,_n_,_v_,_e_,_r_,_t_,_END_,
//	_SHIFT_RIGHT_,  ___,_I_,_n_,_v_,_e_,_r_,_t_,_END_,
//};

//BYTE code _tSTRING_SERVICE_FREQ[] =
//{
//	_SHIFT_RIGHT_,  ___,_F_,_r_,_q_,_u_,_e_,_n_,_c_,_y_,_END_,
//	_SHIFT_RIGHT_,  ___,_F_,_r_,_q_,_u_,_e_,_n_,_c_,_y_,_END_,
//	_SHIFT_RIGHT_,  ___,_F_,_r_,_q_,_u_,_e_,_n_,_c_,_y_,_END_,
//	_SHIFT_RIGHT_,  ___,_F_,_r_,_q_,_u_,_e_,_n_,_c_,_y_,_END_,
//	_SHIFT_RIGHT_,  ___,_F_,_r_,_q_,_u_,_e_,_n_,_c_,_y_,_END_,
//	_SHIFT_RIGHT_,  ___,_F_,_r_,_q_,_u_,_e_,_n_,_c_,_y_,_END_,
//	_RIGHT_ARROWS_, ___,_F_,_R_,_Q_,_U_,_E_,_N_,_C_,_Y_,_END_, // Russia
//	_SHIFT_RIGHT_,  ___,_F_,_r_,_q_,_u_,_e_,_n_,_c_,_y_,_END_,
//	_SHIFT_RIGHT_,  ___,_F_,_r_,_q_,_u_,_e_,_n_,_c_,_y_,_END_,
//};

BYTE code _tSTRING_SERVICE_255[] =
{
	 _8_,_B_,_i_,_t_,_SHIFT_RIGHT_,  ___,_2_,_5_,_5_,_END_,
	 _8_,_B_,_i_,_t_,_SHIFT_RIGHT_,  ___,_2_,_5_,_5_,_END_,
	 _8_,_B_,_i_,_t_,_SHIFT_RIGHT_,  ___,_2_,_5_,_5_,_END_,
	 _8_,_B_,_i_,_t_,_SHIFT_RIGHT_,  ___,_2_,_5_,_5_,_END_,
	 _8_,_B_,_i_,_t_,_SHIFT_RIGHT_,  ___,_2_,_5_,_5_,_END_,
	 _8_,_B_,_i_,_t_,_SHIFT_RIGHT_,  ___,_2_,_5_,_5_,_END_,
	 _8_,_B_,_I_,_T_,_RIGHT_ARROWS_, ___,_2_,_5_,_5_,_END_, // Russia
	 _8_,_B_,_i_,_t_,_SHIFT_RIGHT_,  ___,_2_,_5_,_5_,_END_,
	 _8_,_B_,_I_,_T_,0xa5,___,_2_,_5_,_5_,_END_,
};

BYTE code _tSTRING_SERVICE_4095[] =
{
	_1_,_2_,_B_,_i_,_t_,_SHIFT_RIGHT_,  ___,_4_,_0_,_9_,_5_,_END_,
	_1_,_2_,_B_,_i_,_t_,_SHIFT_RIGHT_,  ___,_4_,_0_,_9_,_5_,_END_,
	_1_,_2_,_B_,_i_,_t_,_SHIFT_RIGHT_,  ___,_4_,_0_,_9_,_5_,_END_,
	_1_,_2_,_B_,_i_,_t_,_SHIFT_RIGHT_,  ___,_4_,_0_,_9_,_5_,_END_,
	_1_,_2_,_B_,_i_,_t_,_SHIFT_RIGHT_,  ___,_4_,_0_,_9_,_5_,_END_,
	_1_,_2_,_B_,_i_,_t_,_SHIFT_RIGHT_,  ___,_4_,_0_,_9_,_5_,_END_,
	_1_,_2_,_B_,_I_,_T_,_RIGHT_ARROWS_, ___,_4_,_0_,_9_,_5_,_END_, // Russia
	_1_,_2_,_B_,_i_,_t_,_SHIFT_RIGHT_,  ___,_4_,_0_,_9_,_5_,_END_,
	_1_,_2_,_B_,_I_,_T_,0xa5,___,_4_,_0_,_9_,_5_,_END_,
};

BYTE code _tSTRING_SERVICE_CURVE[] =
{
	_C_,_u_,_r_,_v_,_e_,_END_,
	_C_,_u_,_r_,_v_,_e_,_END_,
	_C_,_u_,_r_,_v_,_e_,_END_,
	_C_,_u_,_r_,_v_,_e_,_END_,
	_C_,_u_,_r_,_v_,_e_,_END_,
	_C_,_u_,_r_,_v_,_e_,_END_,
	_C_,_U_,_R_,_V_,_E_,_END_, // Russia
	_C_,_u_,_r_,_v_,_e_,_END_,
	_C_,_U_,_R_,_V_,_E_,_END_,
};

BYTE code _tSTRING_SERVICE_LINEAR[] =
{
	_L_,_i_,_n_,_e_,_a_,_r_,_END_,
	_L_,_i_,_n_,_e_,_a_,_r_,_END_,
	_L_,_i_,_n_,_e_,_a_,_r_,_END_,
	_L_,_i_,_n_,_e_,_a_,_r_,_END_,
	_L_,_i_,_n_,_e_,_a_,_r_,_END_,
	_L_,_i_,_n_,_e_,_a_,_r_,_END_,
	_L_,_I_,_N_,_E_,_A_,_R_,_END_, // Russia
	_L_,_i_,_n_,_e_,_a_,_r_,_END_,
	_L_,_I_,_N_,_E_,_A_,_R_,_END_,
};

#if (_ENABLE_MENU_OLED == _ON)
BYTE code _tSTRING_OLED_SETTINGS[] =
{
	_O_,_L_,_E_,_D_,___,_S_, _e_, _t_, _t_, _i_, _n_, _g_, _s_,_END_,
	_O_,_L_,_E_,_D_,___,_S_, _e_, _t_, _t_, _i_, _n_, _g_, _s_,_END_,
	_O_,_L_,_E_,_D_,___,_S_, _e_, _t_, _t_, _i_, _n_, _g_, _s_,_END_,
	_O_,_L_,_E_,_D_,___,_S_, _e_, _t_, _t_, _i_, _n_, _g_, _s_,_END_,
	_O_,_L_,_E_,_D_,___,_S_, _e_, _t_, _t_, _i_, _n_, _g_, _s_,_END_,
	_O_,_L_,_E_,_D_,___,_S_, _e_, _t_, _t_, _i_, _n_, _g_, _s_,_END_,
	_O_,_L_,_E_,_D_,___,_S_, _E_, _T_, _T_, _I_, _N_, _G_, _S_,_END_,
	_O_,_L_,_E_,_D_,___,_S_, _e_, _t_, _t_, _i_, _n_, _g_, _s_,_END_,
	_O_,_L_,_E_,_D_,___,0x2d,___, 0x2e,_END_,//
};

BYTE code _tSTRING_OLED_OFFRS[] =
{
	_O_,_L_,_E_,_D_,___,_O_,_F_,_F_,_SLINE_,_R_,_S_,_END_,
	_O_,_L_,_E_,_D_,___,_O_,_F_,_F_,_SLINE_,_R_,_S_,_END_,
	_O_,_L_,_E_,_D_,___,_O_,_F_,_F_,_SLINE_,_R_,_S_,_END_,
	_O_,_L_,_E_,_D_,___,_O_,_F_,_F_,_SLINE_,_R_,_S_,_END_,
	_O_,_L_,_E_,_D_,___,_O_,_F_,_F_,_SLINE_,_R_,_S_,_END_,
	_O_,_L_,_E_,_D_,___,_O_,_F_,_F_,_SLINE_,_R_,_S_,_END_,
	_O_,_L_,_E_,_D_,___,_O_,_F_,_F_,_SLINE_,_R_,_S_,_END_,
	_O_,_L_,_E_,_D_,___,_O_,_F_,_F_,_SLINE_,_R_,_S_,_END_,
	_O_,_L_,_E_,_D_,___,_O_,_F_,_F_,0x76,_R_,_S_,_END_,
};

BYTE code _tSTRING_OLED_JB[] =
{
	_O_,_L_,_E_,_D_,___,_J_,_B_,_END_,
	_O_,_L_,_E_,_D_,___,_J_,_B_,_END_,
	_O_,_L_,_E_,_D_,___,_J_,_B_,_END_,
	_O_,_L_,_E_,_D_,___,_J_,_B_,_END_,
	_O_,_L_,_E_,_D_,___,_J_,_B_,_END_,
	_O_,_L_,_E_,_D_,___,_J_,_B_,_END_,
	_O_,_L_,_E_,_D_,___,_J_,_B_,_END_,
	_O_,_L_,_E_,_D_,___,_J_,_B_,_END_,
	_O_,_L_,_E_,_D_,___,_J_,_B_,_END_,
};
#endif

BYTE code tSTRING_AUTO_COLOR[] =
{
	_A_,_U_,_T_,_O_,_,_C_,_O_,_L_,_O_,_R_,_END_,
};



//_tSTRING_NO_SIGNAL
 BYTE code tSTRING_NO_SUPPORT[] =
 {
	 _N_,_O_,_,_S_,_U_,_P_,_P_,_O_,_R_,_T_,_END_,
 };
#if 0

 BYTE code tSTRING_PASS[] =
 {
	 _P_,_a_,_s_,_s_,_END_,
 };
 
 BYTE code tSTRING_FAIL[] =
 {
	 _F_,_a_,_i_,_l_,_END_,
 };
 
//170928_01
BYTE code tSTRING_CONNECT_BLUETOOTH_MSG0[] =
{
 //   _A_, _r_, _e_, _,_Y_, _o_, _u_,_, _S_, _u_,_r_, _e_, _, _t_, _o_, _, _C_, _o_,_n_, _n_, _e_, _c_,_t_,_, _B_, _l_,_u_,_e_, _t_, _o_,_o_,_t_, _QUERY_,  _END_,
   _A_, _r_, _e_, _,_Y_, _o_, _u_,_, _S_, _u_,_r_, _e_, _, _t_, _o_, _, _C_, _o_,_n_, _n_, _e_, _c_,_t_,_, _B_, _T_, _QUERY_,  _END_,

};
BYTE code tSTRING_CONNECT_BLUETOOTH_MSG1[] =
{
    _C_, _o_, _n_, _n_, _e_,_c_, _t_, _i_, _o_, _n_, _,_COLON_, _, _T_, _h_, _e_, _, _S_,_c_, _r_, _e_, _e_, _n_,_, _i_, _s_,_, _c_,_l_, _o_, _s_,_e_,  _d_, _DOT_, _END_,
};

BYTE code tSTRING_DISCONNECT_BLUETOOTH_MSG0[] =
{
    _B_, _l_, _u_, _e_, _t_,_o_, _o_, _t_,_h_, _, _o_,_f_, _f_,_DOT_,  _END_,
};
BYTE code tSTRING_DISCONNECT_BLUETOOTH_MSG1[] =
{
    _S_, _w_, _i_, _t_, _c_,_h_, _, _t_, _o_, _, _T_,_V_, _, _P_, _o_, _w_, _e_, _r_,_, _O_, _f_, _f_, _DOT_,_END_,
};

BYTE code tSTRING_AUDIO_STANDARD[] =
{
 _S_,  _t_,  _a_,  _n_, _d_, _a_,_r_,_d_, _END_,
};
BYTE code tSTRING_AUDIO_MOVIE[] =
{
 _M_, _o_, _v_, _i_, _e_, _END_,
};
BYTE code tSTRING_AUDIO_SPORTS[] =
{
 _S_, _p_, _o_, _r_, _t_, _s_, _END_,
};
BYTE code tSTRING_AUDIO_MUSIC[] =
{
 _M_, _u_, _s_, _i_, _c_, _END_,
};

BYTE code tSTRING_COLOREFFECT_STANDARD[] =
{
 _S_,  _t_,  _a_,  _n_, _d_, _a_,_r_,_d_, _END_,
};
BYTE code tSTRING_COLOREFFECT_GAME[] =
{
 _G_,  _a_,  _m_,  _e_, _END_,
};
BYTE code tSTRING_COLOREFFECT_MOVIE[] =
{
 _M_,  _o_,  _v_,  _i_, _e_, _END_,
};
BYTE code tSTRING_COLOREFFECT_PHOTO[] =
{
 _P_,  _h_,  _o_,  _t_, _o_,  _END_,
};
BYTE code tSTRING_COLOREFFECT_VIVID[] =
{
 _V_,  _i_,  _v_,  _i_, _d_, _END_,
};
BYTE code tSTRING_COLOREFFECT_USER[] =
{
 _U_,  _s_,  _e_,  _r_, _END_,
};
#endif
	 
 WORD code tSTRING_RESOLUTION_TABLE[][6]=
 {
	 {	 _,   _,   _,	_,	 _,   _},
	 { 240, _4_, _8_, _0_, _I_,   _},
	 { 480, _4_, _8_, _0_, _P_,   _},
	 { 288, _5_, _7_, _6_, _I_,   _},
	 { 576, _5_, _7_, _6_, _P_,   _},
	 { 720, _7_, _2_, _0_, _P_,   _},
	 { 540, _1_, _0_, _8_, _0_, _I_},
	 {1080, _1_, _0_, _8_, _0_, _P_},
 };

 BYTE code tSTRING_5SEC[] =
 {
	 _5_, ___, _S_, _e_, _c_, _END_,
 };
 BYTE code tSTRING_30SEC[] =
 {
	 _3_, _0_, ___, _S_, _e_, _c_, _END_,
 };
 BYTE code tSTRING_1MIN[] =
 {
	 _1_, ___, _M_, _i_, _n_, _END_,
 };
 BYTE code tSTRING_2MIN[] =
 {
	 _2_, ___, _M_, _i_, _n_, _END_,
 };
 BYTE code tSTRING_5MIN[] =
 {
	_5_, ___, _M_, _i_, _n_, _END_,
	_5_, ___, _M_, _i_, _n_, _END_,
	_5_, ___, _M_, _i_, _n_, _END_,
	_5_, ___, _M_, _i_, _n_, _END_,
	_5_, ___, _M_, _i_, _n_, _END_,
	_5_, ___, _M_, _i_, _n_, _END_,
	_5_, ___, _M_, _I_, _N_, _END_, // Russia
	_5_, ___, _M_, _i_, _n_, _END_,
	_5_, ___, _M_, _i_, _n_, _END_,
 };

 BYTE code tSTRING_10MIN[] =
 {
	_1_,_0_, ___, _M_, _i_, _n_, _END_,
	_1_,_0_, ___, _M_, _i_, _n_, _END_,
	_1_,_0_, ___, _M_, _i_, _n_, _END_,
	_1_,_0_, ___, _M_, _i_, _n_, _END_,
	_1_,_0_, ___, _M_, _i_, _n_, _END_,
	_1_,_0_, ___, _M_, _i_, _n_, _END_,
	_1_,_0_, ___, _M_, _I_, _N_, _END_, // Russia
	_1_,_0_, ___, _M_, _i_, _n_, _END_,
	_1_,_0_, ___, _M_, _i_, _n_, _END_,
 };

 BYTE code tSTRING_15MIN[] =
 {
	_1_,_5_, ___, _M_, _i_, _n_, _END_,
	_1_,_5_, ___, _M_, _i_, _n_, _END_,
	_1_,_5_, ___, _M_, _i_, _n_, _END_,
	_1_,_5_, ___, _M_, _i_, _n_, _END_,
	_1_,_5_, ___, _M_, _i_, _n_, _END_,
	_1_,_5_, ___, _M_, _i_, _n_, _END_,
	_1_,_5_, ___, _M_, _I_, _N_, _END_, // Russia
	_1_,_5_, ___, _M_, _i_, _n_, _END_,
	_1_,_5_, ___, _M_, _i_, _n_, _END_,
 };
 BYTE code tSTRING_20MIN[] =
 {
	_2_,_0_, ___, _M_, _i_, _n_, _END_,
	_2_,_0_, ___, _M_, _i_, _n_, _END_,
	_2_,_0_, ___, _M_, _i_, _n_, _END_,
	_2_,_0_, ___, _M_, _i_, _n_, _END_,
	_2_,_0_, ___, _M_, _i_, _n_, _END_,
	_2_,_0_, ___, _M_, _i_, _n_, _END_,
	_2_,_0_, ___, _M_, _I_, _N_, _END_, // Russia
	_2_,_0_, ___, _M_, _i_, _n_, _END_,
	_2_,_0_, ___, _M_, _i_, _n_, _END_,
 };

 BYTE code tSTRING_30MIN[] =
 {
	 _3_, _0_, ___, _M_, _i_, _n_, _END_,
 };

 BYTE code tSTRING_60MIN[] =
 {
	 _6_, _0_, ___, _M_, _i_, _n_, _END_,
 };

 BYTE code tSTRING_120MIN[] =
 {
	 _1_, _2_, _0_, ___, _M_, _i_, _n_, _END_,
 };

 BYTE code tSTRING_AUTOSELECT[] =
 {
	 _A_ , _u_ , _t_ , _o_ , ___ , _S_ , _e_ , _l_ , _e_ , _c_ , _t_ , _END_,
 };

 BYTE code tSTRING_VERSION[] =
 {
	 _1_, _2_, _0_,_END_,
 };

 
//Eric_020180307 : Delete
//    
//    BYTE code tsOsdNull[] =
//    {
//    U004E,U0075,U006C,U006C,_END_,
//    U7121_2_0,U7121_2_1,_END_,
//    };//tsOsdNull
//    
//    BYTE code tsOsdPicture[] =
//    {
//    U0050,U0069,U0063,U0074,U0075,U0072,U0065,_END_,
//    U5716_2_0,U5716_2_1,U50CF_2_0,U50CF_2_1,_END_,
//    };//tsOsdPicture
//    
//    BYTE code tsOsdDisplay[] =
//    {
//    U0044,U0069,U0073,U0070,U006C,U0061,U0079,_END_,
//    _FONT_SELECT_EXT1,U986F_2_0,_FONT_SELECT_EXT1,U986F_2_1,U793A_2_0,U793A_2_1,_END_,
//    };//tsOsdDisplay
//    
//    BYTE code tsOsdColor[] =
//    {
//    U0043,U006F,U006C,U006F,U0072,_END_,
//    _FONT_SELECT_EXT1,U984F_2_0,_FONT_SELECT_EXT1,U984F_2_1,U8272_2_0,U8272_2_1,_END_,
//    };//tsOsdColor
//    
//    BYTE code tsOsdAdvance[] =
//    {
//    U0041,U0064,U0076,U0061,U006E,U0063,U0065,_END_,
//    _FONT_SELECT_EXT1,U9032_2_0,_FONT_SELECT_EXT1,U9032_2_1,_FONT_SELECT_EXT1,U968E_2_0,_FONT_SELECT_EXT1,U968E_2_1,_END_,
//    };//tsOsdAdvance
//    
//    BYTE code tsOsdInput[] =
//    {
//    U0049,U006E,U0070,U0075,U0074,_END_,
//    _FONT_SELECT_EXT1,U8F38_2_0,_FONT_SELECT_EXT1,U8F38_2_1,U5165_2_0,U5165_2_1,_END_,
//    };//tsOsdInput
//    
//    BYTE code tsOsdAudio[] =
//    {
//    U0041,U0075,U0064,U0069,U006F,_END_,
//    _FONT_SELECT_EXT1,U97F3_2_0,_FONT_SELECT_EXT1,U97F3_2_1,_FONT_SELECT_EXT1,U983B_2_0,_FONT_SELECT_EXT1,U983B_2_1,_END_,
//    };//tsOsdAudio
//    
//    BYTE code tsOsdOther[] =
//    {
//    U004F,U0074,U0068,U0065,U0072,_END_,
//    U5176_2_0,U5176_2_1,U5B83_2_0,U5B83_2_1,_END_,
//    };//tsOsdOther
//    
//    BYTE code tsOsdInformation[] =
//    {
//    U0049,U006E,U0066,U006F,U0072,U006D,_FONT_SPACE_1,U0061,U0074,U0069,U006F,U006E,_END_,
//    U8A0A_2_0,U8A0A_2_1,U606F_2_0,U606F_2_1,_END_,
//    };//tsOsdInformation
//    
//    BYTE code tsOsdFactory[] =
//    {
//    U0046,U0061,U0063,U0074,U006F,U0072,U0079,_END_,
//    U5DE5_2_0,U5DE5_2_1,U5EE0_2_0,U5EE0_2_1,_END_,
//    };//tsOsdFactory
//    
//    BYTE code tsOsdBacklight[] =
//    {
//    U0042,U0061,U0063,U006B,U006C,U0069,U0067,U0068,U0074,_END_,
//    U80CC_2_0,U80CC_2_1,U5149_2_0,U5149_2_1,_END_,
//    };//tsOsdBacklight
//    
//    BYTE code tsOsdBrightness[] =
//    {
//    U0042,U0072,U0069,U0067,U0068,U0074,U006E,U0065,U0073,U0073,_END_,
//    U4EAE_2_0,U4EAE_2_1,U5EA6_2_0,U5EA6_2_1,_END_,
//    };//tsOsdBrightness
//    
//    BYTE code tsOsdContrast[] =
//    {
//    U0043,U006F,U006E,U0074,U0072,U0061,U0073,U0074,_END_,
//    U5C0D_2_0,U5C0D_2_1,U6BD4_2_0,U6BD4_2_1,U5EA6_2_0,U5EA6_2_1,_END_,
//    };//tsOsdContrast
//    
//    BYTE code tsOsdSharpness[] =
//    {
//    U0053,U0068,U0061,U0072,U0070,U006E,U0065,U0073,U0073,_END_,
//    _FONT_SELECT_EXT1,U92B3_2_0,_FONT_SELECT_EXT1,U92B3_2_1,U5229_2_0,U5229_2_1,U5EA6_2_0,U5EA6_2_1,_END_,
//    };//tsOsdSharpness
//    
//    BYTE code tsOsdAutoAdjust[] =
//    {
//    U0041,U0075,U0074,U006F,U0020,U0041,U0064,U006A,U0075,U0073,U0074,_END_,
//    U81EA_2,U52D5_2_0,U52D5_2_1,_FONT_SELECT_EXT1,U8ABF_2_0,_FONT_SELECT_EXT1,U8ABF_2_1,U6574_2_0,U6574_2_1,_END_,
//    };//tsOsdAutoAdjust
//    
//    BYTE code tsOsdHPosition[] =
//    {
//    U0048,U0020,U0050,U006F,U0073,U0069,U0074,U0069,U006F,U006E,_END_,
//    U5782_2_0,U5782_2_1,U76F4_2_0,U76F4_2_1,U4F4D_2_0,U4F4D_2_1,U7F6E_2_0,U7F6E_2_1,_END_,
//    };//tsOsdHPosition
//    
//    BYTE code tsOsdVPosition[] =
//    {
//    U0056,U0020,U0050,U006F,U0073,U0069,U0074,U0069,U006F,U006E,_END_,
//    U6C34_2_0,U6C34_2_1,U5E73_2_0,U5E73_2_1,U4F4D_2_0,U4F4D_2_1,U7F6E_2_0,U7F6E_2_1,_END_,
//    };//tsOsdVPosition
//    
//    BYTE code tsOsdClock[] =
//    {
//    U0043,U006C,U006F,U0063,U006B,_END_,
//    U6642_2_0,U6642_2_1,U8108_2_0,U8108_2_1,_END_,
//    };//tsOsdClock
//    
//    BYTE code tsOsdPhase[] =
//    {
//    U0050,U0068,U0061,U0073,U0065,_END_,
//    U76F8_2_0,U76F8_2_1,U4F4D_2_0,U4F4D_2_1,_END_,
//    };//tsOsdPhase
//    
//    BYTE code tsOsdDispRotate[] =
//    {
//    U0044,U0069,U0073,U0070,U0020,U0052,U006F,U0074,U0061,U0074,U0065,_END_,
//    U5F71_2_0,U5F71_2_1,U50CF_2_0,U50CF_2_1,U65CB_2_0,U65CB_2_1,_FONT_SELECT_EXT1,U8F49_2_0,_FONT_SELECT_EXT1,U8F49_2_1,_END_,
//    };//tsOsdDispRotate
//    
//    BYTE code tsOsdDispLatency[] =
//    {
//    U0044,U0069,U0073,U0070,U0020,U004C,U0061,U0074,U0065,U006E,U0063,U0079,_END_,
//    _FONT_SELECT_EXT1,U986F_2_0,_FONT_SELECT_EXT1,U986F_2_1,U793A_2_0,U793A_2_1,U5EF6_2_0,U5EF6_2_1,_FONT_SELECT_EXT1,U9072_2_0,_FONT_SELECT_EXT1,U9072_2_1,_END_,
//    };//tsOsdDispLatency
//    
//    BYTE code tsOsdPanelUniformity[] =
//    {
//    U0050,U0061,U006E,U0065,U006C,U0020,U0055,U006E,U0069,U0066,U006F,U0072,U006D,_FONT_SPACE_1,U0069,U0074,U0079,_END_,
//    U756B_2_0,U756B_2_1,_FONT_SELECT_EXT1,U9762_2_0,_FONT_SELECT_EXT1,U9762_2_1,U5747_2_0,U5747_2_1,U52FB_2_0,U52FB_2_1,U6027_2_0,U6027_2_1,_END_,
//    };//tsOsdPanelUniformity
//    
//    BYTE code tsOsdGamma[] =
//    {
//    U0047,U0061,U006D,_FONT_SPACE_1,U006D,_FONT_SPACE_1,U0061,_END_,
//    U0047,U0061,U006D,_FONT_SPACE_1,U006D,_FONT_SPACE_1,U0061,_END_,
//    };//tsOsdGamma
//    
//    BYTE code tsOsdTemperature[] =
//    {
//    U0054,U0065,U006D,_FONT_SPACE_1,U0070,U0065,U0072,U0061,U0074,U0075,U0072,U0065,_END_,
//    U8272_2_0,U8272_2_1,U6EAB_2_0,U6EAB_2_1,_END_,
//    };//tsOsdTemperature
//    
//    BYTE code tsOsdColorEffect[] =
//    {
//    U0043,U006F,U006C,U006F,U0072,U0020,U0045,U0066,U0066,U0065,U0063,U0074,_END_,
//    _FONT_SELECT_EXT1,U984F_2_0,_FONT_SELECT_EXT1,U984F_2_1,U8272_2_0,U8272_2_1,U6548_2_0,U6548_2_1,U679C_2_0,U679C_2_1,_END_,
//    };//tsOsdColorEffect
//    
//    BYTE code tsOsdDemo[] =
//    {
//    U0044,U0065,U006D,_FONT_SPACE_1,U006F,_END_,
//    U5C55_2_0,U5C55_2_1,U793A_2_0,U793A_2_1,_END_,
//    };//tsOsdDemo
//    
//    BYTE code tsOsdColorFormat[] =
//    {
//    U0043,U006F,U006C,U006F,U0072,U0020,U0046,U006F,U0072,U006D,_FONT_SPACE_1,U0061,U0074,_END_,
//    _FONT_SELECT_EXT1,U984F_2_0,_FONT_SELECT_EXT1,U984F_2_1,U8272_2_0,U8272_2_1,U683C_2_0,U683C_2_1,U5F0F_2_0,U5F0F_2_1,_END_,
//    };//tsOsdColorFormat
//    
//    BYTE code tsOsdPcm[] =
//    {
//    U0050,U0043,U004D,_END_,
//    U0050,U0043,U004D,_END_,
//    };//tsOsdPcm
//    
//    BYTE code tsOsdHue[] =
//    {
//    U0048,U0075,U0065,_END_,
//    U8272_2_0,U8272_2_1,_FONT_SELECT_EXT1,U8ABF_2_0,_FONT_SELECT_EXT1,U8ABF_2_1,_END_,
//    };//tsOsdHue
//    
//    BYTE code tsOsdSaturation[] =
//    {
//    U0053,U0061,U0074,U0075,U0072,U0061,U0074,U0069,U006F,U006E,_END_,
//    _FONT_SELECT_EXT1,U98FD_2_0,_FONT_SELECT_EXT1,U98FD_2_1,U548C_2_0,U548C_2_1,U5EA6_2_0,U5EA6_2_1,_END_,
//    };//tsOsdSaturation
//    
//    BYTE code tsOsdAspectRatio[] =
//    {
//    U0041,U0073,U0070,U0065,U0063,U0074,U0020,U0052,U0061,U0074,U0069,U006F,_END_,
//    _FONT_SELECT_EXT1,U9577_2_0,_FONT_SELECT_EXT1,U9577_2_1,U5BEC_2_0,U5BEC_2_1,U6BD4_2_0,U6BD4_2_1,_END_,
//    };//tsOsdAspectRatio
//    
//    BYTE code tsOsdOverScan[] =
//    {
//    U004F,U0076,U0065,U0072,U0020,U0053,U0063,U0061,U006E,_END_,
//    U004F,U0076,U0065,U0072,U0020,U0053,U0063,U0061,U006E,_END_,
//    };//tsOsdOverScan
//    
//    BYTE code tsOsdOverDrive[] =
//    {
//    U004F,U0076,U0065,U0072,U0020,U0044,U0072,U0069,U0076,U0065,_END_,
//    U53CD_2_0,U53CD_2_1,U61C9_2_0,U61C9_2_1,U6642_2_0,U6642_2_1,_FONT_SELECT_EXT1,U9593_2_0,_FONT_SELECT_EXT1,U9593_2_1,_END_,
//    };//tsOsdOverDrive
//    
//    BYTE code tsOsdDcr[] =
//    {
//    U0044,U0043,U0052,_END_,
//    U52D5_2_0,U52D5_2_1,U614B_2_0,U614B_2_1,U5C0D_2_0,U5C0D_2_1,U6BD4_2_0,U6BD4_2_1,_END_,
//    };//tsOsdDcr
//    
//    BYTE code tsOsdDdcci[] =
//    {
//    U0044,U0044,U0043,U0043,U0049,_END_,
//    U0044,U0044,U0043,U0043,U0049,_END_,
//    };//tsOsdDdcci
//    
//    BYTE code tsOsdUltraVivid[] =
//    {
//    U0055,U006C,U0074,U0072,U0061,U0020,U0056,U0069,U0076,U0069,U0064,_END_,
//    U0055,U006C,U0074,U0072,U0061,U0020,U0056,U0069,U0076,U0069,U0064,_END_,
//    };//tsOsdUltraVivid
//    
//    BYTE code tsOsdDpOption[] =
//    {
//    U0044,U0050,U0020,U004F,U0070,U0074,U0069,U006F,U006E,_END_,
//    U0044,U0050,_FONT_SELECT_EXT1,U9078_2_0,_FONT_SELECT_EXT1,U9078_2_1,_FONT_SELECT_EXT1,U9805_2_0,_FONT_SELECT_EXT1,U9805_2_1,_END_,
//    };//tsOsdDpOption
//    
//    BYTE code tsOsdDpMst[] =
//    {
//    U0044,U0050,U0020,U004D,U0053,U0054,_END_,
//    U0044,U0050,U0020,U004D,U0053,U0054,_END_,
//    };//tsOsdDpMst
//    
//    BYTE code tsOsdDpResolution[] =
//    {
//    U0044,U0050,U0020,U0052,U0065,U0073,U006F,U006C,U0075,U0074,U0069,U006F,U006E,_END_,
//    U0044,U0050,U5206_2_0,U5206_2_1,_FONT_SELECT_EXT1,U8FA8_2_0,_FONT_SELECT_EXT1,U8FA8_2_1,U7387_2_0,U7387_2_1,_END_,
//    };//tsOsdDpResolution
//    
//    BYTE code tsOsdCloneMode[] =
//    {
//    U0043,U006C,U006F,U006E,U0065,U0020,U004D,U006F,U0064,U0065,_END_,
//    U8907_2_0,U8907_2_1,U88FD_2_0,U88FD_2_1,_END_,
//    };//tsOsdCloneMode
//    
//    #if(_FREESYNC_II_SUPPORT == _ON)
//    BYTE code tsOsdFreeSync2[] =
//    {
//    U0046,U0072,U0065,U0065,U0020,U0053,U0079,U006E,U0063,U0032,_END_,
//    U0046,U0072,U0065,U0065,U0020,U0053,U0079,U006E,U0063,U0032,_END_,
//    };//tsOsdFreeSync2
//    
//    #endif //#if(_FREESYNC_II_SUPPORT == _ON)
//    
//    #if(_FREESYNC_II_SUPPORT == _OFF)
//    BYTE code tsOsdFreeSync[] =
//    {
//    U0046,U0072,U0065,U0065,U0020,U0053,U0079,U006E,U0063,_END_,
//    U0046,U0072,U0065,U0065,U0020,U0053,U0079,U006E,U0063,_END_,
//    };//tsOsdFreeSync
//    
//    #endif //#if(_FREESYNC_II_SUPPORT == _OFF)
//    
//    BYTE code tsOsdFreeze[] =
//    {
//    U0046,U0072,U0065,U0065,U007A,U0065,_END_,
//    U51CD_2_0,U51CD_2_1,U7D50_2_0,U7D50_2_1,_END_,
//    };//tsOsdFreeze
//    
//    #if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
//    BYTE code tsOsdTypeCConfig[] =
//    {
//    U0054,U0079,U0070,U0065,U0020,U0043,U0020,U0043,U006F,U006E,U0066,U0069,U0067,_END_,
//    U0054,U0079,U0070,U0065,U0020,U0043,U0020,_FONT_SELECT_EXT1,U914D_2_0,_FONT_SELECT_EXT1,U914D_2_1,U7F6E_2_0,U7F6E_2_1,_END_,
//    };//tsOsdTypeCConfig
//    
//    #endif //#if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
//    
//    #if(_HDR10_SUPPORT == _ON)
//    BYTE code tsOsdUltraHdr[] =
//    {
//    U0055,U006C,U0074,U0072,U0061,U0020,U0048,U0044,U0052,_END_,
//    U0055,U006C,U0074,U0072,U0061,U0020,U0048,U0044,U0052,_END_,
//    };//tsOsdUltraHdr
//    
//    BYTE code tsOsdUltraHdrMode[] =
//    {
//    U0055,U006C,U0074,U0072,U0061,U0020,U0048,U0044,U0052,U0020,U004D,U006F,U0064,U0065,_END_,
//    U0055,U006C,U0074,U0072,U0061,U0020,U0048,U0044,U0052,U0020,U004D,U006F,U0064,U0065,_END_,
//    };//tsOsdUltraHdrMode
//    
//    BYTE code tsOsdDarkEnhance[] =
//    {
//    U0044,U0061,U0072,U006B,U0020,U0045,U006E,U0068,U0061,U006E,U0063,U0065,_END_,
//    _FONT_SELECT_EXT1,U9ED1_2_0,_FONT_SELECT_EXT1,U9ED1_2_1,_FONT_SELECT_EXT1,U90E8_2_0,_FONT_SELECT_EXT1,U90E8_2_1,U589E_2_0,U589E_2_1,U5F37_2_0,U5F37_2_1,_END_,
//    };//tsOsdDarkEnhance
//    
//    BYTE code tsOsdSharpnessEnhance[] =
//    {
//    U0053,U0068,U0061,U0072,U0070,U0020,U0045,U006E,U0068,U0061,U006E,U0063,U0065,_END_,
//    _FONT_SELECT_EXT1,U92B3_2_0,_FONT_SELECT_EXT1,U92B3_2_1,U5229_2_0,U5229_2_1,U5EA6_2_0,U5EA6_2_1,U589E_2_0,U589E_2_1,U5F37_2_0,U5F37_2_1,_END_,
//    };//tsOsdSharpnessEnhance
//    
//    BYTE code tsOsdColorEnhance[] =
//    {
//    U0043,U006F,U006C,U006F,U0072,U0020,U0045,U006E,U0068,U0061,U006E,U0063,U0065,_END_,
//    _FONT_SELECT_EXT1,U984F_2_0,_FONT_SELECT_EXT1,U984F_2_1,U8272_2_0,U8272_2_1,U589E_2_0,U589E_2_1,U5F37_2_0,U5F37_2_1,_END_,
//    };//tsOsdColorEnhance
//    
//    BYTE code tsOsdLightEnhance[] =
//    {
//    U004C,U0069,U0067,U0068,U0074,U0020,U0045,U006E,U0068,U0061,U006E,U0063,U0065,_END_,
//    U4EAE_2_0,U4EAE_2_1,U5EA6_2_0,U5EA6_2_1,U589E_2_0,U589E_2_1,U5F37_2_0,U5F37_2_1,_END_,
//    };//tsOsdLightEnhance
//    
//    #endif //#if(_HDR10_SUPPORT == _ON)
//    
//    #if(_OSD_LOCAL_DIMMING_SUPPORT == _ON)
//    BYTE code tsOsdLocalDimming[] =
//    {
//    U004C,U006F,U0063,U0061,U006C,U0020,U0044,U0069,U006D,_FONT_SPACE_1,U006D,_FONT_SPACE_1,U0069,U006E,U0067,_END_,
//    U5C40_2_0,U5C40_2_1,_FONT_SELECT_EXT1,U90E8_2_0,_FONT_SELECT_EXT1,U90E8_2_1,_FONT_SELECT_EXT1,U8ABF_2_0,_FONT_SELECT_EXT1,U8ABF_2_1,U5149_2_0,U5149_2_1,_END_,
//    };//tsOsdLocalDimming
//    
//    #endif //#if(_OSD_LOCAL_DIMMING_SUPPORT == _ON)
//    
//    #if(_PIXEL_SHIFT_SUPPORT == _ON)
//    BYTE code tsOsdPixelShifting[] =
//    {
//    U0050,U0069,U0078,U0065,U006C,U0020,U0053,U0068,U0069,U0066,U0074,U0069,U006E,U0067,_END_,
//    U50CF_2_0,U50CF_2_1,U7D20_2_0,U7D20_2_1,U79FB_2_0,U79FB_2_1,U4F4D_2_0,U4F4D_2_1,_END_,
//    };//tsOsdPixelShifting
//    
//    #endif //#if(_PIXEL_SHIFT_SUPPORT == _ON)
//    
//    BYTE code tsOsdHdmiVersion[] =
//    {
//    U0048,U0044,U004D,U0049,U0020,U0056,U0065,U0072,U0073,U0069,U006F,U006E,_END_,
//    U0048,U0044,U004D,U0049,U0020,U7248_2_0,U7248_2_1,U672C_2_0,U672C_2_1,_END_,
//    };//tsOsdHdmiVersion
//    
//    #if(_SDR_TO_HDR_SUPPORT == _ON)
//    BYTE code tsOsdSdrToHdr[] =
//    {
//    U0053,U0044,U0052,U0020,U0054,U006F,U0020,U0048,U0044,U0052,_END_,
//    U0053,U0044,U0052,U0020,U0054,U006F,U0020,U0048,U0044,U0052,_END_,
//    };//tsOsdSdrToHdr
//    
//    #endif //#if(_SDR_TO_HDR_SUPPORT == _ON)
//    
//    BYTE code tsOsdAutoSelect[] =
//    {
//    U0041,U0075,U0074,U006F,U0020,U0053,U0065,U006C,U0065,U0063,U0074,_END_,
//    U81EA_2,U52D5_2_0,U52D5_2_1,_FONT_SELECT_EXT1,U9078_2_0,_FONT_SELECT_EXT1,U9078_2_1,U64C7_2_0,U64C7_2_1,_END_,
//    };//tsOsdAutoSelect
//    
//    BYTE code tsOsdVolume[] =
//    {
//    U0056,U006F,U006C,U0075,U006D,_FONT_SPACE_1,U0065,_END_,
//    _FONT_SELECT_EXT1,U97F3_2_0,_FONT_SELECT_EXT1,U97F3_2_1,_FONT_SELECT_EXT1,U91CF_2_0,_FONT_SELECT_EXT1,U91CF_2_1,_END_,
//    };//tsOsdVolume
//    
//    BYTE code tsOsdMute[] =
//    {
//    U004D,U0075,U0074,U0065,_END_,
//    _FONT_SELECT_EXT1,U9759_2_0,_FONT_SELECT_EXT1,U9759_2_1,_FONT_SELECT_EXT1,U97F3_2_0,_FONT_SELECT_EXT1,U97F3_2_1,_END_,
//    };//tsOsdMute
//    
//    BYTE code tsOsdStandAlong[] =
//    {
//    U0053,U0074,U0061,U006E,U0064,U0020,U0041,U006C,U006F,U006E,U0067,_END_,
//    U7368_2_0,U7368_2_1,U7ACB_2_0,U7ACB_2_1,_END_,
//    };//tsOsdStandAlong
//    
//    BYTE code tsOsdAudioSource[] =
//    {
//    U0041,U0075,U0064,U0069,U006F,U0020,U0053,U006F,U0075,U0072,U0063,U0065,_END_,
//    _FONT_SELECT_EXT1,U97F3_2_0,_FONT_SELECT_EXT1,U97F3_2_1,U6E90_2_0,U6E90_2_1,_END_,
//    };//tsOsdAudioSource
//    
//    BYTE code tsOsdSoundMode[] =
//    {
//    U0053,U006F,U0075,U006E,U0064,U0020,U004D,U006F,U0064,U0065,_END_,
//    U8072_2_0,U8072_2_1,_FONT_SELECT_EXT1,U97F3_2_0,_FONT_SELECT_EXT1,U97F3_2_1,U6A21_2_0,U6A21_2_1,U5F0F_2_0,U5F0F_2_1,_END_,
//    };//tsOsdSoundMode
//    
//    #if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
//    BYTE code tsOsdAudioSelfTest[] =
//    {
//    U0041,U0075,U0064,U0069,U006F,U0020,U0053,U0065,U006C,U0066,U0020,U0054,U0065,U0073,U0074,_END_,
//    U0041,U0075,U0064,U0069,U006F,U0020,U0053,U0065,U006C,U0066,U0020,U0054,U0065,U0073,U0074,_END_,
//    };//tsOsdAudioSelfTest
//    
//    #endif //#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
//    
//    BYTE code tsOsdReset[] =
//    {
//    U0052,U0065,U0073,U0065,U0074,_END_,
//    _FONT_SELECT_EXT1,U91CD_2_0,_FONT_SELECT_EXT1,U91CD_2_1,U7F6E_2_0,U7F6E_2_1,_END_,
//    };//tsOsdReset
//    
//    BYTE code tsOsdMenuTime[] =
//    {
//    U004D,U0065,U006E,U0075,U0020,U0054,U0069,U006D,_FONT_SPACE_1,U0065,_END_,
//    _FONT_SELECT_EXT1,U9078_2_0,_FONT_SELECT_EXT1,U9078_2_1,U55AE_2_0,U55AE_2_1,U6642_2_0,U6642_2_1,_FONT_SELECT_EXT1,U9593_2_0,_FONT_SELECT_EXT1,U9593_2_1,_END_,
//    };//tsOsdMenuTime
//    
//    BYTE code tsOsdOsdHPosition[] =
//    {
//    U004F,U0053,U0044,U0020,U0048,U0020,U0050,U006F,U0073,U0069,U0074,U0069,U006F,U006E,_END_,
//    U004F,U0053,U0044,U0020,U5782_2_0,U5782_2_1,U76F4_2_0,U76F4_2_1,U4F4D_2_0,U4F4D_2_1,U7F6E_2_0,U7F6E_2_1,_END_,
//    };//tsOsdOsdHPosition
//    
//    BYTE code tsOsdOsdVPosition[] =
//    {
//    U004F,U0053,U0044,U0020,U0056,U0020,U0050,U006F,U0073,U0069,U0074,U0069,U006F,U006E,_END_,
//    U004F,U0053,U0044,U0020,U6C34_2_0,U6C34_2_1,U5E73_2_0,U5E73_2_1,U4F4D_2_0,U4F4D_2_1,U7F6E_2_0,U7F6E_2_1,_END_,
//    };//tsOsdOsdVPosition
//    
//    BYTE code tsOsdLanguage[] =
//    {
//    U004C,U0061,U006E,U0067,U0075,U0061,U0067,U0065,_END_,
//    _FONT_SELECT_EXT1,U8A9E_2_0,_FONT_SELECT_EXT1,U8A9E_2_1,U8A00_2_0,U8A00_2_1,_END_,
//    };//tsOsdLanguage
//    
//    BYTE code tsOsdTransparency[] =
//    {
//    U0054,U0072,U0061,U006E,U0073,U0070,U0061,U0072,U0065,U006E,U0063,U0079,_END_,
//    _FONT_SELECT_EXT1,U900F_2_0,_FONT_SELECT_EXT1,U900F_2_1,U660E_2_0,U660E_2_1,U5EA6_2_0,U5EA6_2_1,_END_,
//    };//tsOsdTransparency
//    
//    BYTE code tsOsdRotate[] =
//    {
//    U0052,U006F,U0074,U0061,U0074,U0065,_END_,
//    U65CB_2_0,U65CB_2_1,_FONT_SELECT_EXT1,U8F49_2_0,_FONT_SELECT_EXT1,U8F49_2_1,_END_,
//    };//tsOsdRotate
//    
//    BYTE code tsOsdUserMode[] =
//    {
//    U0055,U0073,U0065,U0072,U0020,U004D,U006F,U0064,U0065,U0020,U003A,_END_,
//    U4F7F_2_0,U4F7F_2_1,U7528_2_0,U7528_2_1,U8005_2_0,U8005_2_1,U6A21_2_0,U6A21_2_1,U5F0F_2_0,U5F0F_2_1,U0020,U003A,_END_,
//    };//tsOsdUserMode
//    
//    BYTE code tsOsdPresetMode[] =
//    {
//    U0050,U0072,U0065,U0073,U0065,U0074,U0020,U004D,U006F,U0064,U0065,U0020,U003A,_END_,
//    _FONT_SELECT_EXT1,U9810_2_0,_FONT_SELECT_EXT1,U9810_2_1,_FONT_SELECT_EXT1,U8A2D_2_0,_FONT_SELECT_EXT1,U8A2D_2_1,U6A21_2_0,U6A21_2_1,U5F0F_2_0,U5F0F_2_1,U0020,U003A,_END_,
//    };//tsOsdPresetMode
//    
//    BYTE code tsOsdPleaseWait[] =
//    {
//    U0050,U006C,U0065,U0061,U0073,U0065,U0020,U0057_0,U0057_1,U0061,U0069,U0074,_END_,
//    _FONT_SELECT_EXT1,U8ACB_2_0,_FONT_SELECT_EXT1,U8ACB_2_1,U7A0D_2_0,U7A0D_2_1,U5019_2_0,U5019_2_1,_END_,
//    };//tsOsdPleaseWait
//    
//    BYTE code tsOsdNoCable[] =
//    {
//    U004E,U006F,U0020,U0043,U0061,U0062,U006C,U0065,_END_,
//    U7121_2_0,U7121_2_1,U8A0A_2_0,U8A0A_2_1,U865F_2_0,U865F_2_1,U7DDA_2_0,U7DDA_2_1,_END_,
//    };//tsOsdNoCable
//    
//    BYTE code tsOsdNoSignal[] =
//    {
//    U004E,U006F,U0020,U0053,U0069,U0067,U006E,U0061,U006C,_END_,
//    U7121_2_0,U7121_2_1,U8A0A_2_0,U8A0A_2_1,U865F_2_0,U865F_2_1,_END_,
//    };//tsOsdNoSignal
//    
//    BYTE code tsOsdNoSupport[] =
//    {
//    U004E,U006F,U0020,U0053,U0075,U0070,U0070,U006F,U0072,U0074,_END_,
//    U4E0D_2_0,U4E0D_2_1,U652F_2_0,U652F_2_1,U63F4_2_0,U63F4_2_1,_END_,
//    };//tsOsdNoSupport
//    
//    BYTE code tsOsdAutoColor[] =
//    {
//    U0041,U0075,U0074,U006F,U0020,U0043,U006F,U006C,U006F,U0072,_END_,
//    U81EA_2,U52D5_2_0,U52D5_2_1,_FONT_SELECT_EXT1,U8ABF_2_0,_FONT_SELECT_EXT1,U8ABF_2_1,U8272_2_0,U8272_2_1,_END_,
//    };//tsOsdAutoColor
//    
//    BYTE code tsOsdGoToPowerSaving[] =
//    {
//    U0047,U006F,U0020,U0054,U006F,U0020,U0050,U006F,U0077_0,U0077_1,U0065,U0072,U0020,U0053,U0061,U0076,U0069,U006E,U0067,_END_,
//    _FONT_SELECT_EXT1,U9032_2_0,_FONT_SELECT_EXT1,U9032_2_1,U5165_2_0,U5165_2_1,U7701_2_0,U7701_2_1,_FONT_SELECT_EXT1,U96FB_2_0,_FONT_SELECT_EXT1,U96FB_2_1,U6A21_2_0,U6A21_2_1,U5F0F_2_0,U5F0F_2_1,_END_,
//    };//tsOsdGoToPowerSaving
//    
//    BYTE code tsOsdPass[] =
//    {
//    U0050,U0061,U0073,U0073,_END_,
//    U0050,U0061,U0073,U0073,_END_,
//    };//tsOsdPass
//    
//    BYTE code tsOsdFail[] =
//    {
//    U0046,U0061,U0069,U006C,_END_,
//    U0046,U0061,U0069,U006C,_END_,
//    };//tsOsdFail
//    
//    BYTE code tsOsdStr480i[] =
//    {
//    U0034,U0038,U0030,U0069,_END_,
//    U0034,U0038,U0030,U0069,_END_,
//    };//tsOsdStr480i
//    
//    BYTE code tsOsdStr480p[] =
//    {
//    U0034,U0038,U0030,U0050,_END_,
//    U0034,U0038,U0030,U0050,_END_,
//    };//tsOsdStr480p
//    
//    BYTE code tsOsdStr576i[] =
//    {
//    U0035,U0037,U0036,U0069,_END_,
//    U0035,U0037,U0036,U0069,_END_,
//    };//tsOsdStr576i
//    
//    BYTE code tsOsdStr576p[] =
//    {
//    U0035,U0037,U0036,U0050,_END_,
//    U0035,U0037,U0036,U0050,_END_,
//    };//tsOsdStr576p
//    
//    BYTE code tsOsdStr720p[] =
//    {
//    U0037,U0032,U0030,U0050,_END_,
//    U0037,U0032,U0030,U0050,_END_,
//    };//tsOsdStr720p
//    
//    BYTE code tsOsdStr1080i[] =
//    {
//    U0031,U0030,U0038,U0030,U0069,_END_,
//    U0031,U0030,U0038,U0030,U0069,_END_,
//    };//tsOsdStr1080i
//    
//    BYTE code tsOsdStr1080p[] =
//    {
//    U0031,U0030,U0038,U0030,U0050,_END_,
//    U0031,U0030,U0038,U0030,U0050,_END_,
//    };//tsOsdStr1080p

//--------------------------------------------------
