#ifndef _TA3782F_H_
#define _TA3782F_H_
/*****************************************************************************/
/* Include files */
/*****************************************************************************/
#include "intrins.h"
#include <CMS\CMS80F262x.H>
/*****************************************************************************/
/* Global pre-processor symbols/macros ('#define') */
/*****************************************************************************/
typedef int32_t  s32;
typedef int16_t  s16;
typedef int8_t   s8;

typedef uint32_t  u32;
typedef uint16_t  u16;
typedef uint8_t   u8;

/*-----------SFR(特殊功能寄存器)-------*/
sfr   I2CSSR = 0xf2;
sfr   I2CMSR = 0xf5;

/*--------------------------------------------------------------- --------
  BIT Register  
-------------------------------------------------------------------------*/
/*  P0  */
  sbit P07  = P0^7;
  sbit P06  = P0^6;
  sbit P05  = P0^5;
  sbit P04  = P0^4;
  sbit P03  = P0^3;
  sbit P02  = P0^2;
  sbit P01  = P0^1;
  sbit P00  = P0^0;
/*  P1  */
  sbit P17  = P1^7;
  sbit P16  = P1^6;
  sbit P15  = P1^5;
  sbit P14  = P1^4;
  sbit P13  = P1^3;
  sbit P12  = P1^2;
  sbit P11  = P1^1;
  sbit P10  = P1^0;  
  
/*  P2  */
  sbit P27  = P2^7;
  sbit P26  = P2^6;
  sbit P25  = P2^5;
  sbit P24  = P2^4;
  sbit P23  = P2^3;
  sbit P22  = P2^2;
  sbit P21  = P2^1;
  sbit P20  = P2^0;
/*  P3  */
  sbit P37  = P3^7;
  sbit P36  = P3^6;
  sbit P35  = P3^5;
  sbit P34  = P3^4;
  sbit P33  = P3^3;
  sbit P32  = P3^2;
  sbit P31  = P3^1;
  sbit P30  = P3^0;
/*  P4  */
  sbit P47  = P4^7;
  sbit P46  = P4^6;
  sbit P45  = P4^5;
  sbit P44  = P4^4;
  sbit P43  = P4^3;
  sbit P42  = P4^2;
  sbit P41  = P4^1;
  sbit P40  = P4^0;
	/*  P5  */
  sbit P55  = P5^5;
  sbit P54  = P5^4;
  sbit P53  = P5^3;
  sbit P52  = P5^2;
  sbit P51  = P5^1;
  sbit P50  = P5^0;
 
/*****************************************************************************/
/* Global type definitions ('typedef') */
/*****************************************************************************/

/*-----------------------------------------------------------------
**	Peripheral memory map
------------------------------------------------------------------*/

/*-----------------------------------------------------------------
**IRQ 中断 
------------------------------------------------------------------*/
/*------IE--------------------------------------------------------*/
#define IRQ_IE_EA_Pos			(7)
#define IRQ_IE_EA_Msk			(0x1 << IRQ_IE_EA_Pos)
#define IRQ_IE_ES1_Pos			(6)
#define IRQ_IE_ES1_Msk			(0x1 << IRQ_IE_ES1_Pos)
#define IRQ_IE_ET2_Pos			(5)
#define IRQ_IE_ET2_Msk			(0x1 << IRQ_IE_ET2_Pos)
#define IRQ_IE_ES0_Pos			(4)
#define IRQ_IE_ES0_Msk			(0x1 << IRQ_IE_ES0_Pos)
#define IRQ_IE_ET1_Pos			(3)
#define IRQ_IE_ET1_Msk			(0x1 << IRQ_IE_ET1_Pos)
#define IRQ_IE_EX1_Pos			(2)
#define IRQ_IE_EX1_Msk			(0x1 << IRQ_IE_EX1_Pos)
#define IRQ_IE_ET0_Pos			(1)
#define IRQ_IE_ET0_Msk			(0x1 << IRQ_IE_ET0_Pos)
#define IRQ_IE_EX0_Pos			(0)
#define IRQ_IE_EX0_Msk			(0x1 << IRQ_IE_EX0_Pos)

/*------EIE2------------------------------------------------------*/
#define IRQ_EIE2_SPIIE_Pos		(7)
#define IRQ_EIE2_SPIIE_Msk		(0x1 << IRQ_EIE2_SPIIE_Pos)
#define IRQ_EIE2_I2CIE_Pos		(6)
#define IRQ_EIE2_I2CIE_Msk		(0x1 << IRQ_EIE2_I2CIE_Pos)
#define IRQ_EIE2_WDTIE_Pos		(5)
#define IRQ_EIE2_WDTIE_Msk		(0x1 << IRQ_EIE2_WDTIE_Pos)
#define IRQ_EIE2_ADCIE_Pos		(4)
#define IRQ_EIE2_ADCIE_Msk		(0x1 << IRQ_EIE2_ADCIE_Pos)
#define IRQ_EIE2_PWMIE_Pos		(3)
#define IRQ_EIE2_PWMIE_Msk		(0x1 << IRQ_EIE2_PWMIE_Pos)
#define IRQ_EIE2_ET4IE_Pos		(1)
#define IRQ_EIE2_ET4IE_Msk		(0x1 << IRQ_EIE2_ET4IE_Pos)
#define IRQ_EIE2_ET3IE_Pos		(0)
#define IRQ_EIE2_ET3IE_Msk		(0x1 << IRQ_EIE2_ET3IE_Pos)
/*------EIE3------------------------------------------------------*/
#define IRQ_EIE3_ES3_Pos		(1)
#define IRQ_EIE3_ES3_Msk		(0x1 << IRQ_EIE3_ES3_Pos)
#define IRQ_EIE3_ES2_Pos		(0)
#define IRQ_EIE3_ES2_Msk		(0x1 << IRQ_EIE3_ES2_Pos)
/*------T2IE------------------------------------------------------*/
#define IRQ_T2IE_T2OVIE_Pos		(7)
#define IRQ_T2IE_T2OVIE_Msk		(0x1 << IRQ_T2IE_T2OVIE_Pos)
#define IRQ_T2IE_T2EXIE_Pos		(6)
#define IRQ_T2IE_T2EXIE_Msk		(0x1 << IRQ_T2IE_T2EXIE_Pos)
#define IRQ_T2IE_T2C3IE_Pos		(3)
#define IRQ_T2IE_T2C3IE_Msk		(0x1 << IRQ_T2IE_T2C3IE_Pos)
#define IRQ_T2IE_T2C2IE_Pos		(2)
#define IRQ_T2IE_T2C2IE_Msk		(0x1 << IRQ_T2IE_T2C2IE_Pos)
#define IRQ_T2IE_T2C1IE_Pos		(1)
#define IRQ_T2IE_T2C1IE_Msk		(0x1 << IRQ_T2IE_T2C1IE_Pos)
#define IRQ_T2IE_T2C0IE_Pos		(0)
#define IRQ_T2IE_T2C0IE_Msk		(0x1 << IRQ_T2IE_T2C0IE_Pos)


/*------EIF2------------------------------------------------------*/
#define IRQ_EIF2_SPIIF_Pos		(7)
#define IRQ_EIF2_SPIIF_Msk		(0x1 << IRQ_EIF2_SPIIF_Pos)
#define IRQ_EIF2_I2CIF_Pos		(6)
#define IRQ_EIF2_I2CIF_Msk		(0x1 << IRQ_EIF2_I2CIF_Pos)
#define IRQ_EIF2_ADCIF_Pos		(4)
#define IRQ_EIF2_ADCIF_Msk		(0x1 << IRQ_EIF2_ADCIF_Pos)
#define IRQ_EIF2_PWMIF_Pos		(3)
#define IRQ_EIF2_PWMIF_Msk		(0x1 << IRQ_EIF2_PWMIF_Pos)
#define IRQ_EIF2_TF4_Pos		(1)
#define IRQ_EIF2_TF4_Msk		(0x1 << IRQ_EIF2_TF4_Pos)
#define IRQ_EIF2_TF3_Pos		(0)
#define IRQ_EIF2_TF3_Msk		(0x1 << IRQ_EIF2_TF3_Pos)

/*------T2IF------------------------------------------------------*/
#define IRQ_T2IF_T2F_Pos		(7)
#define IRQ_T2IF_T2F_Msk		(0x1 << IRQ_T2IF_T2F_Pos)
#define IRQ_T2IF_T2EXIF_Pos		(6)
#define IRQ_T2IF_T2EXIF_Msk		(0x1 << IRQ_T2IF_T2EXIF_Pos)
#define IRQ_T2IF_T2C3IF_Pos		(3)
#define IRQ_T2IF_T2C3IF_Msk		(0x1 << IRQ_T2IF_T2C3IF_Pos)
#define IRQ_T2IF_T2C2IF_Pos		(2)
#define IRQ_T2IF_T2C2IF_Msk		(0x1 << IRQ_T2IF_T2C2IF_Pos)
#define IRQ_T2IF_T2C1IF_Pos		(1)
#define IRQ_T2IF_T2C1IF_Msk		(0x1 << IRQ_T2IF_T2C1IF_Pos)
#define IRQ_T2IF_T2C0IF_Pos		(0)
#define IRQ_T2IF_T2C0IF_Msk		(0x1 << IRQ_T2IF_T2C0IF_Pos)

/*-----------------------------------------------------------------
**System CLK  
------------------------------------------------------------------*/
/*------SCKSEL----------------------------------------------------*/
#define SYS_SCKSEL_SEL_Pos				(4)
#define SYS_SCKSEL_SEL_Msk				(0x1 << SYS_SCKSEL_SEL_Pos)
#define SYS_SCKSEL_WRITE_Pos			(3)
#define SYS_SCKSEL_WRITE_Msk			(0x1 << SYS_SCKSEL_WRITE_Pos)
#define SYS_SCKSEL_CKSEL_Pos			(0)
#define SYS_SCKSEL_CKSEL_Msk			(0x7 << SYS_SCKSEL_CKSEL_Pos)
/*------SCKSTAU---------------------------------------------------*/
#define SYS_SCKSTAU_LSIF_Pos			(7)
#define SYS_SCKSTAU_LSIF_Msk			(0x1 << SYS_SCKSTAU_LSIF_Pos)
#define SYS_SCKSTAU_LSEF_Pos			(6)
#define SYS_SCKSTAU_LSEF_Msk			(0x1 << SYS_SCKSTAU_LSEF_Pos)
#define SYS_SCKSTAU_HSEF_Pos			(5)
#define SYS_SCKSTAU_HSEF_Msk			(0x1 << SYS_SCKSTAU_HSEF_Pos)
#define SYS_SCKSTAU_HSIF_Pos			(4)
#define SYS_SCKSTAU_HSIF_Msk			(0x1 << SYS_SCKSTAU_HSIF_Pos)
/*------PCON------------------------------------------------------*/
#define SYS_PCON_SMOD0_Pos			(7)
#define SYS_PCON_SMOD0_Msk			(0x1 << SYS_PCON_SMOD0_Pos)
#define SYS_PCON_SMOD1_Pos			(6)
#define SYS_PCON_SMOD1_Msk			(0x1 << SYS_PCON_SMOD1_Pos)
#define SYS_PCON_SWE_Pos			(2)
#define SYS_PCON_SWE_Msk			(0x1 << SYS_PCON_SWE_Pos)
#define SYS_PCON_STOP_Pos			(1)
#define SYS_PCON_STOP_Msk			(0x1 << SYS_PCON_STOP_Pos)
#define SYS_PCON_IDLE_Pos			(0)
#define SYS_PCON_IDLE_Msk			(0x1 << SYS_PCON_IDLE_Pos)

/*------XT_SCM----------------------------------------------------*/
#define SYS_XTSCM_SCMEN_Pos			(7)
#define SYS_XTSCM_SCMEN_Msk			(0x1 << SYS_XTSCM_SCMEN_Pos)
#define SYS_XTSCM_SCMIE_Pos			(6)
#define SYS_XTSCM_SCMIE_Msk			(0x1 << SYS_XTSCM_SCMIE_Pos)
#define SYS_XTSCM_SCMIF_Pos			(1)
#define SYS_XTSCM_SCMIF_Msk			(0x1 << SYS_XTSCM_SCMIF_Pos)
#define SYS_XTSCM_SCMSTA_Pos		(0)
#define SYS_XTSCM_SCMSTA_Msk		(0x1 << SYS_XTSCM_SCMSTA_Pos)

/*-----------------------------------------------------------------
**LVD
------------------------------------------------------------------*/
/*------LVDCON-----------------------------------------------------*/
#define LVD_LVDCON_LVDSEL_Pos		(4)
#define LVD_LVDCON_LVDSEL_Msk		(0xf << LVD_LVDCON_LVDSEL_Pos)
#define LVD_LVDCON_LVDEN_Pos		(3)
#define LVD_LVDCON_LVDEN_Msk		(0x1 << LVD_LVDCON_LVDEN_Pos)
#define LVD_LVDCON_LVDOUT_Pos		(2)
#define LVD_LVDCON_LVDOUT_Msk		(0x1 << LVD_LVDCON_LVDOUT_Pos)
#define LVD_LVDCON_LVDINTF_Pos		(0)
#define LVD_LVDCON_LVDINTF_Msk		(0x1 << LVD_LVDCON_LVDINTF_Pos)

/*-----------------------------------------------------------------
**WDT
------------------------------------------------------------------*/
/*------WDCON-----------------------------------------------------*/
#define WDT_WDCON_SWRST_Pos			(7)
#define WDT_WDCON_SWRST_Msk			(0x1 << WDT_WDCON_SWRST_Pos)
#define WDT_WDCON_PORF_Pos			(6)
#define WDT_WDCON_PORF_Msk			(0x1 << WDT_WDCON_PORF_Pos)
#define WDT_WDCON_EXTIF_Pos			(5)
#define WDT_WDCON_EXTIF_Msk			(0x1 << WDT_WDCON_EXTIF_Pos)
#define WDT_WDCON_FIXIF_Pos			(4)
#define WDT_WDCON_FIXIF_Msk			(0x1 << WDT_WDCON_FIXIF_Pos)
#define WDT_WDCON_WDTIF_Pos			(3)
#define WDT_WDCON_WDTIF_Msk			(0x1 << WDT_WDCON_WDTIF_Pos)
#define WDT_WDCON_WDTRF_Pos			(2)
#define WDT_WDCON_WDTRF_Msk			(0x1 << WDT_WDCON_WDTRF_Pos)
#define WDT_WDCON_WDTRE_Pos			(1)
#define WDT_WDCON_WDTRE_Msk			(0x1 << WDT_WDCON_WDTRE_Pos)
#define WDT_WDCON_WDTCLR_Pos		(0)
#define WDT_WDCON_WDTCLR_Msk		(0x1 << WDT_WDCON_WDTCLR_Pos)
/*-----------------------------------------------------------------
**WUT
------------------------------------------------------------------*/
/*------WUTCRH----------------------------------------------------*/
#define WUT_WUTCRH_WUTEN_Pos		(7)
#define WUT_WUTCRH_WUTEN_Msk		(0x1 << WUT_WUTCRH_WUTEN_Pos)
#define WUT_WUTCRH_TMROV_Pos		(6)
#define WUT_WUTCRH_TMROV_Msk		(0x1 << WUT_WUTCRH_TMROV_Pos)
#define WUT_WUTCRH_WUTPS_Pos		(4)
#define WUT_WUTCRH_WUTPS_Msk		(0x3 << WUT_WUTCRH_WUTPS_Pos)
#define WUT_WUTCRH_WUTD_Pos			(0)
#define WUT_WUTCRH_WUTD_Msk			(0xF << WUT_WUTCRH_WUTD_Pos)

/*-----------------------------------------------------------------
**Timer
------------------------------------------------------------------*/
/*------TMOD------------------------------------------------------*/
#define TMR_TMOD_GATE1_Pos				(7)
#define TMR_TMOD_GATE1_Msk				(0x1 << TMR_TMOD_GATE1_Pos)
#define TMR_TMOD_CT1_Pos				(6)
#define TMR_TMOD_CT1_Msk				(0x1 << TMR_TMOD_CT1_Pos)
#define TMR_TMOD_T1Mn_Pos				(4)
#define TMR_TMOD_T1Mn_Msk				(0x3 << TMR_TMOD_T1Mn_Pos)
#define TMR_TMOD_GATE0_Pos				(3)
#define TMR_TMOD_GATE0_Msk				(0x1 << TMR_TMOD_GATE0_Pos)
#define TMR_TMOD_CT0_Pos				(2)
#define TMR_TMOD_CT0_Msk				(0x1 << TMR_TMOD_CT0_Pos)
#define TMR_TMOD_T0Mn_Pos				(0)
#define TMR_TMOD_T0Mn_Msk				(0x3 << TMR_TMOD_T0Mn_Pos)
/*------TCON------------------------------------------------------*/
#define TMR_TCON_TF1_Pos				(7)
#define TMR_TCON_TF1_Msk				(0x1 << TMR_TCON_TF1_Pos)
#define TMR_TCON_TR1_Pos				(6)
#define TMR_TCON_TR1_Msk				(0x1 << TMR_TCON_TR1_Pos)
#define TMR_TCON_TF0_Pos				(5)
#define TMR_TCON_TF0_Msk				(0x1 << TMR_TCON_TF0_Pos)
#define TMR_TCON_TR0_Pos				(4)
#define TMR_TCON_TR0_Msk				(0x1 << TMR_TCON_TR0_Pos)
#define TMR_TCON_IE1_Pos				(3)
#define TMR_TCON_IE1_Msk				(0x1 << TMR_TCON_IE1_Pos)
#define TMR_TCON_IT1_Pos				(2)
#define TMR_TCON_IT1_Msk				(0x1 << TMR_TCON_IT1_Pos)
#define TMR_TCON_IE0_Pos				(1)
#define TMR_TCON_IE0_Msk				(0x1 << TMR_TCON_IE0_Pos)
#define TMR_TCON_IT0_Pos				(0)
#define TMR_TCON_IT0_Msk				(0x1 << TMR_TCON_IT0_Pos)
/*------CKCON-----------------------------------------------------*/
#define TMR_CKCON_WTSn_Pos				(5)
#define TMR_CKCON_WTSn_Msk				(0x7 << TMR_CKCON_WTSn_Pos)
#define TMR_CKCON_T1M_Pos				(4)
#define TMR_CKCON_T1M_Msk				(0x1 << TMR_CKCON_T1M_Pos)
#define TMR_CKCON_T0M_Pos				(3)
#define TMR_CKCON_T0M_Msk				(0x1 << TMR_CKCON_T0M_Pos)
#define TMR_CKCON_T0CNTM_Pos			(0)
#define TMR_CKCON_T0CNTM_Msk			(0x1 << TMR_CKCON_T0CNTM_Pos)

/*------T2CON-----------------------------------------------------*/
#define TMR_T2CON_T2PS_Pos				(7)
#define TMR_T2CON_T2PS_Msk				(0x1 << TMR_T2CON_T2PS_Pos)
#define TMR_T2CON_I3FR_Pos				(6)
#define TMR_T2CON_I3FR_Msk				(0x1 << TMR_T2CON_I3FR_Pos)
#define TMR_T2CON_CAPES_Pos				(5)
#define TMR_T2CON_CAPES_Msk				(0x1 << TMR_T2CON_CAPES_Pos)
#define TMR_T2CON_T2R_Pos				(3)
#define TMR_T2CON_T2R_Msk				(0x3 << TMR_T2CON_T2R_Pos)
#define TMR_T2CON_T2CM_Pos				(2)
#define TMR_T2CON_T2CM_Msk				(0x1 << TMR_T2CON_T2CM_Pos)
#define TMR_T2CON_T2I_Pos				(0)
#define TMR_T2CON_T2I_Msk				(0x3 << TMR_T2CON_T2I_Pos)

/*------CCEN------------------------------------------------------*/
#define TMR_CCEN_CMn3_Pos				(6)
#define TMR_CCEN_CMn3_Msk				(0x3 << TMR_CCEN_CMn3_Pos)
#define TMR_CCEN_CMn2_Pos				(4)
#define TMR_CCEN_CMn2_Msk				(0x3 << TMR_CCEN_CMn2_Pos)
#define TMR_CCEN_CMn1_Pos				(2)
#define TMR_CCEN_CMn1_Msk				(0x3 << TMR_CCEN_CMn1_Pos)
#define TMR_CCEN_CMn0_Pos				(0)
#define TMR_CCEN_CMn0_Msk				(0x3 << TMR_CCEN_CMn0_Pos)

/*------CAP2CON--------------------------------------------------*/
#define TMR_CAP2CON_CAP2EER_Pos			(7)
#define TMR_CAP2CON_CAP2EER_Msk			(0x1 << TMR_CAP2CON_CAP2EER_Pos)
#define TMR_CAP2CON_CAP2LOCK_Pos		(3)
#define TMR_CAP2CON_CAP2LOCK_Msk		(0x1 << TMR_CAP2CON_CAP2LOCK_Pos)
#define TMR_CAP2CON_CAP2CLR_Pos			(2)
#define TMR_CAP2CON_CAP2CLR_Msk			(0x1 << TMR_CAP2CON_CAP2CLR_Pos)
#define TMR_CAP2CON_CAP2ST_Pos			(1)
#define TMR_CAP2CON_CAP2ST_Msk			(0x1 << TMR_CAP2CON_CAP2ST_Pos)
#define TMR_CAP2CON_CAP2EN_Pos			(0)
#define TMR_CAP2CON_CAP2EN_Msk			(0x1 << TMR_CAP2CON_CAP2EN_Pos)


/*------T34MOD----------------------------------------------------*/
#define TMR_T34MOD_TR4_Pos				(7)
#define TMR_T34MOD_TR4_Msk				(0x1 << TMR_T34MOD_TR4_Pos)
#define TMR_T34MOD_T4M_Pos				(6)
#define TMR_T34MOD_T4M_Msk				(0x1 << TMR_T34MOD_T4M_Pos)
#define TMR_T34MOD_T4Mn_Pos				(4)
#define TMR_T34MOD_T4Mn_Msk				(0x3 << TMR_T34MOD_T4Mn_Pos)
#define TMR_T34MOD_TR3_Pos				(3)
#define TMR_T34MOD_TR3_Msk				(0x1 << TMR_T34MOD_TR3_Pos)
#define TMR_T34MOD_T3M_Pos				(2)
#define TMR_T34MOD_T3M_Msk				(0x1 << TMR_T34MOD_T3M_Pos)
#define TMR_T34MOD_T3Mn_Pos				(0)
#define TMR_T34MOD_T3Mn_Msk				(0x3 << TMR_T34MOD_T3Mn_Pos)

/*-----------------------------------------------------------------
**UART
------------------------------------------------------------------*/
/*------SCON0------------------------------------------------------*/
#define UART_SCON0_U0SMn_Pos			(6)
#define UART_SCON0_U0SMn_Msk			(0x3 << UART_SCON0_U0SMn_Pos)
#define UART_SCON0_U0SM2_Pos			(5)
#define UART_SCON0_U0SM2_Msk			(0x1 << UART_SCON0_U0SM2_Pos)
#define UART_SCON0_U0REN_Pos			(4)
#define UART_SCON0_U0REN_Msk			(0x1 << UART_SCON0_U0REN_Pos)
#define UART_SCON0_U0TB8_Pos			(3)
#define UART_SCON0_U0TB8_Msk			(0x1 << UART_SCON0_U0TB8_Pos)
#define UART_SCON0_U0RB8_Pos			(2)
#define UART_SCON0_U0RB8_Msk			(0x1 << UART_SCON0_U0RB8_Pos)
#define UART_SCON0_TI0_Pos				(1)
#define UART_SCON0_TI0_Msk				(0x1 << UART_SCON0_TI0_Pos)
#define UART_SCON0_RI0_Pos				(0)
#define UART_SCON0_RI0_Msk				(0x1 << UART_SCON0_RI0_Pos)
/*------SCON1------------------------------------------------------*/
#define UART_SCON1_U1SMn_Pos			(6)
#define UART_SCON1_U1SMn_Msk			(0x3 << UART_SCON1_U1SMn_Pos)
#define UART_SCON1_U1SM2_Pos			(5)
#define UART_SCON1_U1SM2_Msk			(0x1 << UART_SCON1_U1SM2_Pos)
#define UART_SCON1_U1REN_Pos			(4)
#define UART_SCON1_U1REN_Msk			(0x1 << UART_SCON1_U1REN_Pos)
#define UART_SCON1_U1TB8_Pos			(3)
#define UART_SCON1_U1TB8_Msk			(0x1 << UART_SCON1_U1TB8_Pos)
#define UART_SCON1_U1RB8_Pos			(2)
#define UART_SCON1_U1RB8_Msk			(0x1 << UART_SCON1_U1RB8_Pos)
#define UART_SCON1_TI1_Pos				(1)
#define UART_SCON1_TI1_Msk				(0x1 << UART_SCON1_TI1_Pos)
#define UART_SCON1_RI1_Pos				(0)
#define UART_SCON1_RI1_Msk				(0x1 << UART_SCON1_RI1_Pos)



/*------SCON2------------------------------------------------------*/
#define UART_SCON2_U2SMn_Pos			(6)
#define UART_SCON2_U2SMn_Msk			(0x3 << UART_SCON2_U2SMn_Pos)
#define UART_SCON2_U2SM2_Pos			(5)
#define UART_SCON2_U2SM2_Msk			(0x1 << UART_SCON2_U2SM2_Pos)
#define UART_SCON2_U2REN_Pos			(4)
#define UART_SCON2_U2REN_Msk			(0x1 << UART_SCON2_U2REN_Pos)
#define UART_SCON2_U2TB8_Pos			(3)
#define UART_SCON2_U2TB8_Msk			(0x1 << UART_SCON2_U2TB8_Pos)
#define UART_SCON2_U2RB8_Pos			(2)
#define UART_SCON2_U2RB8_Msk			(0x1 << UART_SCON2_U2RB8_Pos)
#define UART_SCON2_TI2_Pos				(1)
#define UART_SCON2_TI2_Msk				(0x1 << UART_SCON2_TI2_Pos)
#define UART_SCON2_RI2_Pos				(0)
#define UART_SCON2_RI2_Msk				(0x1 << UART_SCON2_RI2_Pos)
/*------SCON3------------------------------------------------------*/
#define UART_SCON3_U3SMn_Pos			(6)
#define UART_SCON3_U3SMn_Msk			(0x3 << UART_SCON3_U3SMn_Pos)
#define UART_SCON3_U3SM2_Pos			(5)
#define UART_SCON3_U3SM2_Msk			(0x1 << UART_SCON3_U3SM2_Pos)
#define UART_SCON3_U3REN_Pos			(4)
#define UART_SCON3_U3REN_Msk			(0x1 << UART_SCON3_U3REN_Pos)
#define UART_SCON3_U3TB8_Pos			(3)
#define UART_SCON3_U3TB8_Msk			(0x1 << UART_SCON3_U3TB8_Pos)
#define UART_SCON3_U3RB8_Pos			(2)
#define UART_SCON3_U3RB8_Msk			(0x1 << UART_SCON3_U3RB8_Pos)
#define UART_SCON3_TI3_Pos				(1)
#define UART_SCON3_TI3_Msk				(0x1 << UART_SCON3_TI3_Pos)
#define UART_SCON3_RI3_Pos				(0)
#define UART_SCON3_RI3_Msk				(0x1 << UART_SCON3_RI3_Pos)


/*------FUNCCR----------------------------------------------------*/
#define SYS_FUNCCR_UART1_CKS_Pos	(4)
#define SYS_FUNCCR_UART1_CKS_Msk	(0x7 << SYS_FUNCCR_UART1_CKS_Pos)
#define SYS_FUNCCR_UART0_CKS_Pos	(0)
#define SYS_FUNCCR_UART0_CKS_Msk	(0x7 << SYS_FUNCCR_UART0_CKS_Pos)

/*------BRTCON-----------------------------------------------------*/
#define UART_BRTCON_BRTEN_Pos			(7)
#define UART_BRTCON_BRTEN_Msk			(0x1 << UART_BRTCON_BRTEN_Pos)
#define UART_BRTCON_BRTCKDIV_Pos		(0)
#define UART_BRTCON_BRTCKDIV_Msk		(0x7 << UART_BRTCON_BRTCKDIV_Pos)
/*------BRT1CON-----------------------------------------------------*/
#define UART_BRT1CON_BRT1EN_Pos			(7)
#define UART_BRT1CON_BRT1EN_Msk			(0x1 << UART_BRT1CON_BRT1EN_Pos)
#define UART_BRT1CON_BRT1CKDIV_Pos		(0)
#define UART_BRT1CON_BRT1CKDIV_Msk		(0x7 << UART_BRT1CON_BRT1CKDIV_Pos)


/*------PCON1------------------------------------------------------*/
#define SYS_PCON1_SMOD3_Pos			(1)
#define SYS_PCON1_SMOD3_Msk			(0x1 << SYS_PCON1_SMOD3_Pos)
#define SYS_PCON1_SMOD2_Pos			(0)
#define SYS_PCON1_SMOD2_Msk			(0x1 << SYS_PCON1_SMOD2_Pos)


/*------FUNCCR1----------------------------------------------------*/
#define SYS_FUNCCR1_UART3_CKS_Pos	(4)
#define SYS_FUNCCR1_UART3_CKS_Msk	(0x7 << SYS_FUNCCR1_UART3_CKS_Pos)
#define SYS_FUNCCR1_UART2_CKS_Pos	(0)
#define SYS_FUNCCR1_UART2_CKS_Msk	(0x7 << SYS_FUNCCR1_UART2_CKS_Pos)



/*-----------------------------------------------------------------
**ADC  
------------------------------------------------------------------*/
/*------ADCON0----------------------------------------------------*/
#define ADC_ADCON0_ADCHS4_Pos		(7)
#define ADC_ADCON0_ADCHS4_Msk		(0x1 << ADC_ADCON0_ADCHS4_Pos)
#define ADC_ADCON0_ADFM_Pos			(6)
#define ADC_ADCON0_ADFM_Msk			(0x1 << ADC_ADCON0_ADFM_Pos)
#define ADC_ADCON0_AN31CH_Pos		(2)
#define ADC_ADCON0_AN31CH_Msk		(0x7 << ADC_ADCON0_AN31CH_Pos)
#define ADC_ADCON0_ADGO_Pos			(1)
#define ADC_ADCON0_ADGO_Msk			(0x1 << ADC_ADCON0_ADGO_Pos)

/*------ADCON1----------------------------------------------------*/
#define ADC_ADCON1_ADEN_Pos			(7)
#define ADC_ADCON1_ADEN_Msk			(0x1 << ADC_ADCON1_ADEN_Pos)
#define ADC_ADCON1_ADCKS_Pos		(4)
#define ADC_ADCON1_ADCKS_Msk		(0x7 << ADC_ADCON1_ADCKS_Pos)
#define ADC_ADCON1_ADCHS_Pos		(0)
#define ADC_ADCON1_ADCHS_Msk		(0xF << ADC_ADCON1_ADCHS_Pos)

/*------ADCON2----------------------------------------------------*/
#define ADC_ADCON2_ADCEX_Pos		(7)
#define ADC_ADCON2_ADCEX_Msk		(0x1 << ADC_ADCON2_ADCEX_Pos)
#define ADC_ADCON2_ADTGS_Pos		(4)
#define ADC_ADCON2_ADTGS_Msk		(0x3 << ADC_ADCON2_ADTGS_Pos)
#define ADC_ADCON2_ADEGS_Pos		(2)
#define ADC_ADCON2_ADEGS_Msk		(0x3 << ADC_ADCON2_ADEGS_Pos)

/*------ADCMPC----------------------------------------------------*/
#define ADC_ADCMPC_ADFBEN_Pos		(7)
#define ADC_ADCMPC_ADFBEN_Msk		(0x1 << ADC_ADCMPC_ADFBEN_Pos)
#define ADC_ADCMPC_ADCMPPS_Pos		(6)
#define ADC_ADCMPC_ADCMPPS_Msk		(0x1 << ADC_ADCMPC_ADCMPPS_Pos)
#define ADC_ADCMPC_ADCMPO_Pos		(4)
#define ADC_ADCMPC_ADCMPO_Msk		(0x1 << ADC_ADCMPC_ADCMPO_Pos)
#define ADC_ADCMPC_ADDLY_Pos		(0)
#define ADC_ADCMPC_ADDLY_Msk		(0x3 << ADC_ADCMPC_ADDLY_Pos)
/*------ADCLDO----------------------------------------------------*/
#define ADC_ADCLDO_LDOEN_Pos		(7)
#define ADC_ADCLDO_LDOEN_Msk		(0x1 << ADC_ADCLDO_LDOEN_Pos)
#define ADC_ADCLDO_VSEL_Pos			(5)
#define ADC_ADCLDO_VSEL_Msk			(0x3 << ADC_ADCLDO_VSEL_Pos)

/*-----------------------------------------------------------------
**BUZZER
------------------------------------------------------------------*/
/*------BUZCON----------------------------------------------------*/
#define BUZZER_BUZCON_BUZEN_Pos		(7)
#define BUZZER_BUZCON_BUZEN_Msk		(0x1 << BUZZER_BUZCON_BUZEN_Pos)
#define BUZZER_BUZCON_BUZCKS_Pos	(0)
#define BUZZER_BUZCON_BUZCKS_Msk	(0x3 << BUZZER_BUZCON_BUZCKS_Pos)/*-----------------------------------------------------------------
**FLASH
------------------------------------------------------------------*/
/*------MSTATUS---------------------------------------------------*/
#define FLASH_MSTATUS_MLOCK_Pos		(7)
#define FLASH_MSTATUS_MLOCK_Msk		(0x1 << FLASH_MSTATUS_MLOCK_Pos)
#define FLASH_MSTATUS_ERROR_Pos		(6)
#define FLASH_MSTATUS_ERROR_Msk		(0x1 << FLASH_MSTATUS_ERROR_Pos)
#define FLASH_MSTATUS_CRCASEL_Pos	(5)
#define FLASH_MSTATUS_CRCASEL_Msk	(0x1 << FLASH_MSTATUS_CRCASEL_Pos)
#define FLASH_MSTATUS_CRCCLR_Pos	(4)
#define FLASH_MSTATUS_CRCCLR_Msk	(0x1 << FLASH_MSTATUS_CRCCLR_Pos)
#define FLASH_MSTATUS_START_Pos		(3)
#define FLASH_MSTATUS_START_Msk		(0x1 << FLASH_MSTATUS_START_Pos)
/*-----------------------------------------------------------------
**I2C
------------------------------------------------------------------*/
/*------I2CMCR----------------------------------------------------*/
#define I2C_I2CMCR_RSTS_Pos			(7)
#define I2C_I2CMCR_RSTS_Msk			(0x1 << I2C_I2CMCR_RSTS_Pos)
#define I2C_I2CMCR_ACK_Pos			(3)
#define I2C_I2CMCR_ACK_Msk			(0x1 << I2C_I2CMCR_ACK_Pos)
#define I2C_I2CMCR_STOP_Pos			(2)
#define I2C_I2CMCR_STOP_Msk			(0x1 << I2C_I2CMCR_STOP_Pos)
#define I2C_I2CMCR_START_Pos		(1)
#define I2C_I2CMCR_START_Msk		(0x1 << I2C_I2CMCR_START_Pos)
#define I2C_I2CMCR_RUN_Pos			(0)
#define I2C_I2CMCR_RUN_Msk			(0x1 << I2C_I2CMCR_RUN_Pos)
/*------I2CMSR----------------------------------------------------*/
#define I2C_I2CMSR_I2CMIF_Pos		(7)
#define I2C_I2CMSR_I2CMIF_Msk		(0x1 << I2C_I2CMSR_I2CMIF_Pos)
#define I2C_I2CMSR_BUS_BUSY_Pos		(6)
#define I2C_I2CMSR_BUS_BUSY_Msk		(0x1 << I2C_I2CMSR_BUS_BUSY_Pos)
#define I2C_I2CMSR_IDLE_Pos			(5)
#define I2C_I2CMSR_IDLE_Msk			(0x1 << I2C_I2CMSR_IDLE_Pos)
#define I2C_I2CMSR_ARB_LOST_Pos		(4)
#define I2C_I2CMSR_ARB_LOST_Msk		(0x1 << I2C_I2CMSR_ARB_LOST_Pos)
#define I2C_I2CMSR_DATA_ACK_Pos		(3)
#define I2C_I2CMSR_DATA_ACK_Msk		(0x1 << I2C_I2CMSR_DATA_ACK_Pos)
#define I2C_I2CMSR_ADD_ACK_Pos		(2)
#define I2C_I2CMSR_ADD_ACK_Msk		(0x1 << I2C_I2CMSR_ADD_ACK_Pos)
#define I2C_I2CMSR_ERROR_Pos		(1)
#define I2C_I2CMSR_ERROR_Msk		(0x1 << I2C_I2CMSR_ERROR_Pos)
#define I2C_I2CMSR_BUSY_Pos			(0)
#define I2C_I2CMSR_BUSY_Msk		(0x1 << I2C_I2CMSR_BUSY_Pos)
/*------I2CMSA----------------------------------------------------*/
#define I2C_I2CMSA_SAn_Pos			(1)
#define I2C_I2CMSA_SAn_Msk			(0x7F << I2C_I2CMSA_SAn_Pos)
#define I2C_I2CMSA_RS_Pos			(0)
#define I2C_I2CMSA_RS_Msk			(0x1 << I2C_I2CMSA_RS_Pos)
/*------I2CSCR----------------------------------------------------*/
#define I2C_I2CSCR_RSTS_Pos			(7)
#define I2C_I2CSCR_RSTS_Msk			(0x1 << I2C_I2CSCR_RSTS_Pos)
#define I2C_I2CSCR_DA_Pos			(0)
#define I2C_I2CSCR_DA_Msk			(0x1 << I2C_I2CSCR_DA_Pos)
/*------I2CSSR----------------------------------------------------*/
#define I2C_I2CSSR_SENDFIN_Pos		(2)
#define I2C_I2CSSR_SENDFIN_Msk		(0x1 << I2C_I2CSCR_RSTS_Pos)
#define I2C_I2CSSR_TREQ_Pos			(1)
#define I2C_I2CSSR_TREQ_Msk			(0x1 << I2C_I2CSSR_TREQ_Pos)
#define I2C_I2CSSR_RREQ_Pos			(0)
#define I2C_I2CSSR_RREQ_Msk			(0x1 << I2C_I2CSSR_RREQ_Pos)


/*-----------------------------------------------------------------
**SPI
------------------------------------------------------------------*/
/*------SPCR------------------------------------------------------*/
#define SPI_SPCR_SPEN_Pos			(6)
#define SPI_SPCR_SPEN_Msk			(0x1 << SPI_SPCR_SPEN_Pos)
#define SPI_SPCR_SPR2_Pos			(5)
#define SPI_SPCR_SPR2_Msk			(0x1 << SPI_SPCR_SPR2_Pos)
#define SPI_SPCR_MSTR_Pos			(4)
#define SPI_SPCR_MSTR_Msk			(0x1 << SPI_SPCR_MSTR_Pos)
#define SPI_SPCR_CPOL_Pos			(3)
#define SPI_SPCR_CPOL_Msk			(0x1 << SPI_SPCR_CPOL_Pos)
#define SPI_SPCR_CPHA_Pos			(2)
#define SPI_SPCR_CPHA_Msk			(0x1 << SPI_SPCR_CPHA_Pos)
#define SPI_SPCR_SPRn_Pos			(0)
#define SPI_SPCR_SPRn_Msk			(0x3 << SPI_SPCR_SPRn_Pos)

/*------SPSR------------------------------------------------------*/
#define SPI_SPSR_SPISIF_Pos			(7)
#define SPI_SPSR_SPISIF_Msk			(0x1 << SPI_SPSR_SPISIF_Pos)
#define SPI_SPSR_WCOL_Pos			(6)
#define SPI_SPSR_WCOL_Msk			(0x1 << SPI_SPSR_WCOL_Pos)
#define SPI_SPSR_SSCEN_Pos			(0)
#define SPI_SPSR_SSCEN_Msk			(0x1 << SPI_SPSR_SSCEN_Pos)

/*-----------------------------------------------------------------
**LSE
------------------------------------------------------------------*/
/*------LSE------------------------------------------------------*/
#define LSE_LSECON_LSEEN_Pos		(7)
#define LSE_LSECON_LSEEN_Msk		(0x1 << LSE_LSECON_LSEEN_Pos)
#define LSE_LSECON_LSEWUEN_Pos		(6)
#define LSE_LSECON_LSEWUEN_Msk		(0x1 << LSE_LSECON_LSEWUEN_Pos)
#define LSE_LSECON_LSECNTEN_Pos		(5)
#define LSE_LSECON_LSECNTEN_Msk		(0x1 << LSE_LSECON_LSECNTEN_Pos)
#define LSE_LSECON_LSESTA_Pos		(4)
#define LSE_LSECON_LSESTA_Msk		(0x1 << LSE_LSECON_LSESTA_Pos)
#define LSE_LSECON_LSEIE_Pos		(3)
#define LSE_LSECON_LSEIE_Msk		(0x1 << LSE_LSECON_LSEIE_Pos)
#define LSE_LSECON_LSEIF_Pos		(0)
#define LSE_LSECON_LSEIF_Msk		(0x1 << LSE_LSECON_LSEIF_Pos)

/*-----------------------------------------------------------------
**WWDT
------------------------------------------------------------------*/
/*------WWCON0------------------------------------------------------*/
#define WWDT_WWCON0_WWDTPSC_Pos		(4)
#define WWDT_WWCON0_WWDTPSC_Msk		(0xF << WWDT_WWCON0_WWDTPSC_Pos)
#define WWDT_WWCON0_WWDTEN_Pos		(3)
#define WWDT_WWCON0_WWDTEN_Msk		(0x1 << WWDT_WWCON0_WWDTEN_Pos)
#define WWDT_WWCON0_WWDTRE_Pos		(2)
#define WWDT_WWCON0_WWDTRE_Msk		(0x1 << WWDT_WWCON0_WWDTRE_Pos)
#define WWDT_WWCON0_WWDTCLR_Pos		(1)
#define WWDT_WWCON0_WWDTCLR_Msk		(0x1 << WWDT_WWCON0_WWDTCLR_Pos)
#define WWDT_WWCON0_WWDTRF_Pos		(0)
#define WWDT_WWCON0_WWDTRF_Msk		(0x1 << WWDT_WWCON0_WWDTRF_Pos)
/*------WWCON1------------------------------------------------------*/
#define WWDT_WWCON1_FORCE_Pos		(4)
#define WWDT_WWCON1_FORCE_Msk		(0xF << WWDT_WWCON1_FORCE_Pos)
#define WWDT_WWCON1_MODE_Pos		(3)
#define WWDT_WWCON1_MODE_Msk		(0x1 << WWDT_WWCON1_MODE_Pos)
#define WWDT_WWCON1_WWDTSLE_Pos		(2)
#define WWDT_WWCON1_WWDTSLE_Msk		(0x1 << WWDT_WWCON1_WWDTSLE_Pos)
#define WWDT_WWCON1_WWDTIE_Pos		(1)
#define WWDT_WWCON1_WWDTIE_Msk		(0x1 << WWDT_WWCON1_WWDTIE_Pos)
#define WWDT_WWCON1_WWDTIF_Pos		(0)
#define WWDT_WWCON1_WWDTIF_Msk		(0x1 << WWDT_WWCON1_WWDTIF_Pos)



/*-----------------------------------------------------------------
**EPWM  
------------------------------------------------------------------*/
/*------PWMCON----------------------------------------------------*/
#define EPWM_PWMCON_PWMRUN_Pos			(6)
#define EPWM_PWMCON_PWMRUN_Msk			(0x1 << EPWM_PWMCON_PWMRUN_Pos)
/*------PWMDTE----------------------------------------------------*/
#define EPWM_PWMDTE_PWM45DTE_Pos		(2)
#define EPWM_PWMDTE_PWM45DTE_Msk		(0x1 << EPWM_PWMDTE_PWM45DTE_Pos)
#define EPWM_PWMDTE_PWM23DTE_Pos		(1)
#define EPWM_PWMDTE_PWM23DTE_Msk		(0x1 << EPWM_PWMDTE_PWM23DTE_Pos)
#define EPWM_PWMDTE_PWM01DTE_Pos		(0)
#define EPWM_PWMDTE_PWM01DTE_Msk		(0x1 << EPWM_PWMDTE_PWM01DTE_Pos)

/*------PWMFBKC----------------------------------------------------*/
#define EPWM_PWMFBKC_PWMFBIE_Pos		(7)
#define EPWM_PWMFBKC_PWMFBIE_Msk		(0x1 << EPWM_PWMFBKC_PWMFBIE_Pos)
#define EPWM_PWMFBKC_PWMFBF_Pos			(6)
#define EPWM_PWMFBKC_PWMFBF_Msk			(0x1 << EPWM_PWMFBKC_PWMFBF_Pos)
#define EPWM_PWMFBKC_BRKAF_Pos			(5)
#define EPWM_PWMFBKC_BRKAF_Msk			(0x1 << EPWM_PWMFBKC_BRKAF_Pos)
#define EPWM_PWMFBKC_PWMFBKSW_Pos		(4)
#define EPWM_PWMFBKC_PWMFBKSW_Msk		(0x1 << EPWM_PWMFBKC_PWMFBKSW_Pos)
#define EPWM_PWMFBKC_PWMFBES_Pos		(3)
#define EPWM_PWMFBKC_PWMFBES_Msk		(0x1 << EPWM_PWMFBKC_PWMFBES_Pos)
#define EPWM_PWMFBKC_PWMFBEN_Pos		(1)
#define EPWM_PWMFBKC_PWMFBEN_Msk		(0x1 << EPWM_PWMFBKC_PWMFBEN_Pos)


/*------PWMFBRKC----------------------------------------------------*/
#define EPWM_PWMBRKC_BRKOSF_Pos			(7)
#define EPWM_PWMBRKC_BRKOSF_Msk			(0x1 << EPWM_PWMBRKC_BRKOSF_Pos)
#define EPWM_PWMBRKC_BRKRCS_Pos			(4)
#define EPWM_PWMBRKC_BRKRCS_Msk			(0x7 << EPWM_PWMBRKC_BRKRCS_Pos)
#define EPWM_PWMBRKC_BRKRCLR_Pos		(3)
#define EPWM_PWMBRKC_BRKRCLR_Msk		(0x1 << EPWM_PWMBRKC_BRKRCLR_Pos)
#define EPWM_PWMBRKC_BRKEN_Pos			(2)
#define EPWM_PWMBRKC_BRKEN_Msk			(0x1 << EPWM_PWMBRKC_BRKEN_Pos)
#define EPWM_PWMBRKC_BRKMS_Pos			(0)
#define EPWM_PWMBRKC_BRKMS_Msk			(0x3 << EPWM_PWMBRKC_BRKMS_Pos)


/*-----------------------------------------------------------------
**ACMP  
------------------------------------------------------------------*/
/*------C0CON0----------------------------------------------------*/
#define ACMP_C0CON0_C0EN_Pos		(7)
#define ACMP_C0CON0_C0EN_Msk		(0x1 << ACMP_C0CON0_C0EN_Pos)
#define ACMP_C0CON0_C0COFM_Pos		(6)
#define ACMP_C0CON0_C0COFM_Msk		(0x1 << ACMP_C0CON0_C0COFM_Pos)
#define ACMP_C0CON0_C0N2G_Pos		(5)
#define ACMP_C0CON0_C0N2G_Msk		(0x1 << ACMP_C0CON0_C0N2G_Pos)
#define ACMP_C0CON0_C0NS_Pos		(3)
#define ACMP_C0CON0_C0NS_Msk		(0x3 << ACMP_C0CON0_C0NS_Pos)
#define ACMP_C0CON0_C0PS_Pos		(0)
#define ACMP_C0CON0_C0PS_Msk		(0x7 << ACMP_C0CON0_C0PS_Pos)
/*------C0CON1----------------------------------------------------*/
#define ACMP_C0CON1_C0OUT_Pos		(7)
#define ACMP_C0CON1_C0OUT_Msk		(0x1 << ACMP_C0CON1_C0OUT_Pos)
#define ACMP_C0CON1_C0CRS_Pos		(6)
#define ACMP_C0CON1_C0CRS_Msk		(0x1 << ACMP_C0CON1_C0CRS_Pos)
#define ACMP_C0CON1_C0ADJ_Pos		(0)
#define ACMP_C0CON1_C0ADJ_Msk		(0x1F<< ACMP_C0CON1_C0ADJ_Pos)
/*------C0CON2----------------------------------------------------*/
#define ACMP_C0CON2_C0NS_Pos		(6)
#define ACMP_C0CON2_C0NS_Msk		(0x1 << ACMP_C0CON2_C0NS_Pos)
#define ACMP_C0CON2_C0POS_Pos		(5)
#define ACMP_C0CON2_C0POS_Msk		(0x1 << ACMP_C0CON2_C0POS_Pos)
#define ACMP_C0CON2_C0FE_Pos		(4)
#define ACMP_C0CON2_C0FE_Msk		(0x1 << ACMP_C0CON2_C0FE_Pos)
#define ACMP_C0CON2_C0FS_Pos		(0)
#define ACMP_C0CON2_C0FS_Msk		(0xF << ACMP_C0CON2_C0FS_Pos)


/*------C1CON0----------------------------------------------------*/
#define ACMP_C1CON0_C1EN_Pos		(7)
#define ACMP_C1CON0_C1EN_Msk		(0x1 << ACMP_C1CON0_C1EN_Pos)
#define ACMP_C1CON0_C1COFM_Pos		(6)
#define ACMP_C1CON0_C1COFM_Msk		(0x1 << ACMP_C1CON0_C1COFM_Pos)
#define ACMP_C1CON0_C1N2G_Pos		(5)
#define ACMP_C1CON0_C1N2G_Msk		(0x1 << ACMP_C1CON0_C1N2G_Pos)
#define ACMP_C1CON0_C1NS_Pos		(3)
#define ACMP_C1CON0_C1NS_Msk		(0x3 << ACMP_C1CON0_C1NS_Pos)
#define ACMP_C1CON0_C1PS_Pos		(0)
#define ACMP_C1CON0_C1PS_Msk		(0x7 << ACMP_C1CON0_C1PS_Pos)
/*------C1CON1----------------------------------------------------*/
#define ACMP_C1CON1_C1OUT_Pos		(7)
#define ACMP_C1CON1_C1OUT_Msk		(0x1 << ACMP_C1CON1_C1OUT_Pos)
#define ACMP_C1CON1_C1CRS_Pos		(6)
#define ACMP_C1CON1_C1CRS_Msk		(0x1 << ACMP_C1CON1_C1CRS_Pos)
#define ACMP_C1CON1_C1ADJ_Pos		(0)
#define ACMP_C1CON1_C1ADJ_Msk		(0x1F<< ACMP_C1CON1_C1ADJ_Pos)
/*------C1CON2----------------------------------------------------*/
#define ACMP_C1CON2_C1POS_Pos		(5)
#define ACMP_C1CON2_C1POS_Msk		(0x1 << ACMP_C1CON2_C1POS_Pos)
#define ACMP_C1CON2_C1FE_Pos		(4)
#define ACMP_C1CON2_C1FE_Msk		(0x1 << ACMP_C1CON2_C1FE_Pos)
#define ACMP_C1CON2_C1FS_Pos		(0)
#define ACMP_C1CON2_C1FS_Msk		(0xF << ACMP_C1CON2_C1FS_Pos)

/*------CNVRCON---------------------------------------------------*/
#define ACMP_CNVRCON_CNDIVS_Pos		(5)
#define ACMP_CNVRCON_CNDIVS_Msk		(0x1 << ACMP_CNVRCON_CNDIVS_Pos)
#define ACMP_CNVRCON_CNSVR_Pos		(4)
#define ACMP_CNVRCON_CNSVR_Msk		(0x1 << ACMP_CNVRCON_CNSVR_Pos)
#define ACMP_CNVRCON_CNSVS_Pos		(0)
#define ACMP_CNVRCON_CNSVS_Msk		(0xF << ACMP_CNVRCON_CNSVS_Pos)
/*------CNFBCON---------------------------------------------------*/
#define ACMP_CNFBCON_C1FBPEN_Pos	(7)
#define ACMP_CNFBCON_C1FBPEN_Msk	(0x1 << ACMP_CNFBCON_C1FBPEN_Pos)
#define ACMP_CNFBCON_C0FBPEN_Pos	(6)
#define ACMP_CNFBCON_C0FBPEN_Msk	(0x1 << ACMP_CNFBCON_C0FBPEN_Pos)
#define ACMP_CNFBCON_C1FBPS_Pos		(5)
#define ACMP_CNFBCON_C1FBPS_Msk		(0x1 << ACMP_CNFBCON_C1FBPS_Pos)
#define ACMP_CNFBCON_C0FBPS_Pos		(4)
#define ACMP_CNFBCON_C0FBPS_Msk		(0x1 << ACMP_CNFBCON_C0FBPS_Pos)
#define ACMP_CNFBCON_C1FBEEN_Pos	(3)
#define ACMP_CNFBCON_C1FBEEN_Msk	(0x1 << ACMP_CNFBCON_C1FBEEN_Pos)
#define ACMP_CNFBCON_C0FBEEN_Pos	(2)
#define ACMP_CNFBCON_C0FBEEN_Msk	(0x1 << ACMP_CNFBCON_C0FBEEN_Pos)
#define ACMP_CNFBCON_C1FBES_Pos		(1)
#define ACMP_CNFBCON_C1FBES_Msk		(0x1 << ACMP_CNFBCON_C1FBES_Pos)
#define ACMP_CNFBCON_C0FBES_Pos		(0)
#define ACMP_CNFBCON_C0FBES_Msk		(0x1 << ACMP_CNFBCON_C0FBES_Pos)
/*------CNIE-------------------------------------------------------*/
#define ACMP_CNIE_C1IE_Pos			(1)
#define ACMP_CNIE_C1IE_Msk			(0x1 << ACMP_CNIE_C1IE_Pos)
#define ACMP_CNIE_C0IE_Pos			(0)
#define ACMP_CNIE_C0IE_Msk			(0x1 << ACMP_CNIE_C0IE_Pos)
/*------CNIF-------------------------------------------------------*/
#define ACMP_CNIF_C1IF_Pos			(1)
#define ACMP_CNIF_C1IF_Msk			(0x1 << ACMP_CNIF_C1IF_Pos)
#define ACMP_CNIF_C0IF_Pos			(0)
#define ACMP_CNIF_C0IF_Msk			(0x1 << ACMP_CNIF_C0IF_Pos)

/*------C0HYS-------------------------------------------------------*/
#define ACMP_C0HYS_PNS_Pos			(2)
#define ACMP_C0HYS_PNS_Msk			(0x3 << ACMP_C0HYS_PNS_Pos)
#define ACMP_C0HYS_S_Pos			(0)
#define ACMP_C0HYS_S_Msk			(0x3 << ACMP_C0HYS_S_Pos)
/*------C1HYS-------------------------------------------------------*/
#define ACMP_C1HYS_PNS_Pos			(2)
#define ACMP_C1HYS_PNS_Msk			(0x3 << ACMP_C1HYS_PNS_Pos)
#define ACMP_C1HYS_S_Pos			(0)
#define ACMP_C1HYS_S_Msk			(0x3 << ACMP_C1HYS_S_Pos)

/*------C0CON3-------------------------------------------------------*/
#define ACMP_C0CON3_CTM_Pos			(4)
#define ACMP_C0CON3_CTM_Msk			(0x3 << ACMP_C0CON3_CTM_Pos)
#define ACMP_C0CON3_SSET_Pos		(0)
#define ACMP_C0CON3_SSET_Msk		(0x1 << ACMP_C0CON3_SSET_Pos)

/*------C1CON3-------------------------------------------------------*/
#define ACMP_C1CON3_CTM_Pos			(4)
#define ACMP_C1CON3_CTM_Msk			(0x3 << ACMP_C1CON3_CTM_Pos)
#define ACMP_C1CON3_SSET_Pos		(0)
#define ACMP_C1CON3_SSET_Msk		(0x1 << ACMP_C1CON3_SSET_Pos)


/*-----------------------------------------------------------------
**MDU
------------------------------------------------------------------*/
/*------ARCON----------------------------------------------------*/
#define MDU_ARCON_MDEF_Pos			(7)
#define MDU_ARCON_MDEF_Msk			(0x1 << MDU_ARCON_MDEF_Pos)
#define MDU_ARCON_MDOV_Pos			(6)
#define MDU_ARCON_MDOV_Msk			(0x1 << MDU_ARCON_MDOV_Pos)
#define MDU_ARCON_SLR_Pos			(5)
#define MDU_ARCON_SLR_Msk			(0x1 << MDU_ARCON_SLR_Pos)
#define MDU_ARCON_SCn_Pos			(0)
#define MDU_ARCON_SCn_Msk			(0x1f << MDU_ARCON_SCn_Pos)




/*-----------------------------------------------------------------
**LED
------------------------------------------------------------------*/
/*------LEDCON----------------------------------------------------*/
#define LED_LEDCON_EN_Pos			(7)
#define LED_LEDCON_EN_Msk			(0x1 << LED_LEDCON_EN_Pos)
#define LED_LEDCON_DUTY_Pos			(5)
#define LED_LEDCON_DUTY_Msk			(0x3 << LED_LEDCON_DUTY_Pos)
#define LED_LEDCON_CA_Pos			(4)
#define LED_LEDCON_CA_Msk			(0x1 << LED_LEDCON_CA_Pos)
#define LED_LEDCON_SEL_Pos			(3)
#define LED_LEDCON_SEL_Msk			(0x1 << LED_LEDCON_SEL_Pos)
#define LED_LEDCON_MODE_Pos			(2)
#define LED_LEDCON_MODE_Msk			(0x1 << LED_LEDCON_MODE_Pos)
#define LED_LEDCON_CLKSEL_Pos		(0)
#define LED_LEDCON_CLKSEL_Msk		(0x3 << LED_LEDCON_CLKSEL_Pos)

/*-----------------------------------------------------------------
**LCD
------------------------------------------------------------------*/
/*------LCDCON0----------------------------------------------------*/
#define LCD_LCDCON0_EN_Pos			(7)
#define LCD_LCDCON0_EN_Msk			(0x1 << LCD_LCDCON0_EN_Pos)
#define LCD_LCDCON0_DM_Pos			(4)
#define LCD_LCDCON0_DM_Msk			(0x3 << LCD_LCDCON0_DM_Pos)
#define LCD_LCDCON0_SEL_Pos			(3)
#define LCD_LCDCON0_SEL_Msk			(0x1<< LCD_LCDCON0_SEL_Pos)
#define LCD_LCDCON0_MOD_Pos			(2)
#define LCD_LCDCON0_MOD_Msk			(0x1<< LCD_LCDCON0_MOD_Pos)
#define LCD_LCDCON0_DUTY_Pos		(0)
#define LCD_LCDCON0_DUTY_Msk		(0x3<< LCD_LCDCON0_DUTY_Pos)
/*------LCDCON1----------------------------------------------------*/
#define LCD_LCDCON1_TEN_Pos			(7)
#define LCD_LCDCON1_TEN_Msk			(0x1 << LCD_LCDCON1_TEN_Pos)
#define LCD_LCDCON1_BIAS_Pos		(4)
#define LCD_LCDCON1_BIAS_Msk		(0x3 << LCD_LCDCON1_BIAS_Pos)
#define LCD_LCDCON1_TVS_Pos			(0)
#define LCD_LCDCON1_TVS_Msk			(0xF << LCD_LCDCON1_TVS_Pos)

/*------LCDCON2----------------------------------------------------*/
#define LCD_LCDCON2_LSIEN_Pos		(7)
#define LCD_LCDCON2_LSIEN_Msk		(0x1 << LCD_LCDCON2_LSIEN_Pos)
#define LCD_LCDCON2_SEL_Pos			(4)
#define LCD_LCDCON2_SEL_Msk			(0x3 << LCD_LCDCON2_SEL_Pos)
#define LCD_LCDCON2_PSC_Pos			(0)
#define LCD_LCDCON2_PSC_Msk			(0xF << LCD_LCDCON2_PSC_Pos)

/*------LCDCON3----------------------------------------------------*/
#define LCD_LCDCON3_RM_Pos			(4)
#define LCD_LCDCON3_RM_Msk			(0x3 << LCD_LCDCON3_RM_Pos)
#define LCD_LCDCON3_FCMODE_Pos		(2)
#define LCD_LCDCON3_FCMODE_Msk		(0x1 << LCD_LCDCON3_FCMODE_Pos)
#define LCD_LCDCON3_FCCTL_Pos		(0)
#define LCD_LCDCON3_FCCTL_Msk		(0x3 << LCD_LCDCON3_FCCTL_Pos)

/*------LCDCON4----------------------------------------------------*/
#define LCD_LCDCON4_DR_Pos			(2)
#define LCD_LCDCON4_DR_Msk			(0x7 << LCD_LCDCON4_DR_Pos)
#define LCD_LCDCON4_BUF_Pos			(1)
#define LCD_LCDCON4_BUF_Msk			(0x1 << LCD_LCDCON4_BUF_Pos)
#define LCD_LCDCON4_MOD_Pos			(0)
#define LCD_LCDCON4_MOD_Msk			(0x1 << LCD_LCDCON4_MOD_Pos)

/*-----------------------------------------------------------------
**中断优先级模块编号 Priority Module Number
------------------------------------------------------------------*/
typedef enum  en_Priority_Module{
	IRQ_INT0	=0,
	IRQ_TMR0	=1,
	IRQ_INT1	=2,
	IRQ_TMR1	=3,
	IRQ_UART0	=4,
	IRQ_TMR2	=5,
	IRQ_UART1	=6,
	
	IRQ_P0		=8,
	IRQ_P1		=9,
	IRQ_P2		=10,
	IRQ_P3		=11,
	IRQ_P4		=12,	
	IRQ_P5		=13,	
	IRQ_ACMP    =15, 
	
	IRQ_TMR3	=16,
	IRQ_TMR4	=17,
	IRQ_EPWM	=19,
	IRQ_ADC 	=20,
	IRQ_WDT  	=21,
	IRQ_I2C  	=22,
	IRQ_SPI  	=23,

	IRQ_UART2	=24,
	IRQ_UART3	=25,
	IRQ_LSE		=26,
	
	IRQ_WWDT    =29,	
}en_Priority_Module_t;

/*-----------------------------------------------------------------
**中断优先级 IRQPriority
------------------------------------------------------------------*/
#define  IRQ_PRIORITY_LOW		(0x00)
#define  IRQ_PRIORITY_HIGH		(0x01)	

/********************************************************************************
 ** \brief	 IRQ_SET_PRIORITY
 **			 设置中断优先级
 ** \param [in] none
 ** \return  none
 ******************************************************************************/
#define  IRQ_SET_PRIORITY(IRQ_Module, IRQPriority)  do{\
														if(IRQ_Module <8)\
														{\
															IP &= ~(1<< IRQ_Module);\
															IP |=(IRQPriority<< IRQ_Module);\
														}\
														else if(IRQ_Module <16)\
														{\
															EIP1 &= ~(1<< (IRQ_Module-8));\
															EIP1 |= (IRQPriority<< (IRQ_Module-8));\
														}\
														else if(IRQ_Module <24)\
														{\
															EIP2 &= ~(1<< (IRQ_Module-16));\
															EIP2 |=(IRQPriority<< (IRQ_Module-16));\
														}\
														else if(IRQ_Module <32)\
														{\
															EIP3 &= ~(1<< (IRQ_Module-24));\
															EIP3 |=(IRQPriority<< (IRQ_Module-24));\														
														}\
													}while(0)

/********************************************************************************
 ** \brief	 IRQ_ALL_ENABLE
 **			 使能总中断
 ** \param [in] none
 ** \return  none
 ******************************************************************************/
#define  IRQ_ALL_ENABLE()		do{\
									EA =1;\
								  }while(0)
/********************************************************************************
 ** \brief	 IRQ_ALL_DISABLE
 **			 关闭总中断
 ** \param [in] none
 ** \return  none
 ******************************************************************************/
#define  IRQ_ALL_DISABLE()		do{\
									EA =0;\
								  }while(0)

/********************************************************************************
 ** \brief	 INTERRUPT_ENTER
 **			 进中断压栈SFRS
 ** \param [in] none
 ** \return  none
 ******************************************************************************/
#define  INTERRUPT_ENTER()		do{\
									_push_(SFRS);\
								  }while(0)

/********************************************************************************
 ** \brief	 INTERRUPT_LEAVE
 **			 出中断初栈SFRS
 ** \param [in] none
 ** \return  none
 ******************************************************************************/
#define  INTERRUPT_LEAVE()		do{\
									_pop_(SFRS);\
								  }while(0)		

/*---------中断向量表---------------------------------------------------------
 **   interrupt vector all 28
------------------------------------------------------------------------------*/
 #define         INT0_VECTOR		0
 #define         TMR0_VECTOR		1
 #define         INT1_VECTOR		2
 #define         TMR1_VECTOR   		3
 #define         UART0_VECTOR    	4
 #define         TMR2_VECTOR		5
 #define         UART1_VECTOR    	6							  
 #define         P0EI_VECTOR		7
 #define         P1EI_VECTOR		8
 #define         P2EI_VECTOR		9	
 #define         P3EI_VECTOR		10	
 #define         P4EI_VECTOR		11	
 #define         P5EI_VECTOR		12		
 #define 		 ACMP_VECTOR		14								  
 #define         TMR3_VECTOR		15
 #define         TMR4_VECTOR		16									  
 #define         EPWM_VECTOR		18
 #define         ADC_VECTOR   		19
 #define         WDT_VECTOR     	20
 #define         I2C_VECTOR			21
 #define         SPI_VECTOR			22	
 #define         UART2_VECTOR   	23
 #define         UART3_VECTOR   	24
 #define         LSE_VECTOR    		25
 #define         WWDT_VECTOR		28							  
							  
#define clrwdt()					TA=0xAA, TA=0x55, WDCON=0x01;										  								  
/*****************************************************************************/
/* Global variable declarations ('extern', definition in C source) */
/*****************************************************************************/

/*****************************************************************************/
/* Global function prototypes ('extern', definition in C source) */
/*****************************************************************************/

#endif /* _TA3782F_H_ */
