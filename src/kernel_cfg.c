/*
 *  kernel_cfg.c
 *  Tue Dec 17 12:29:10 2013
 *  SG Version 2.00
 *  sg.exe main.oil -os=ECC2 -IC:/Users/Dan/Dropbox/Uni/Projekter/P5/P5SVN/Software/nxtOSEK/toppers_osek/sg/impl_oil -template=C:/Users/Dan/Dropbox/Uni/Projekter/P5/P5SVN/Software/nxtOSEK/toppers_osek/sg/lego_nxt.sgt
 */
#include "osek_kernel.h"
#include "kernel_id.h"
#include "alarm.h"
#include "interrupt.h"
#include "resource.h"
#include "task.h"

#define __STK_UNIT VP
#define __TCOUNT_STK_UNIT(sz) (((sz) + sizeof(__STK_UNIT) - 1) / sizeof(__STK_UNIT))

#define TNUM_ALARM     8
#define TNUM_COUNTER   1
#define TNUM_ISR2      0
#define TNUM_RESOURCE  2
#define TNUM_TASK      9
#define TNUM_EXTTASK   0

const UINT8 tnum_alarm    = TNUM_ALARM;
const UINT8 tnum_counter  = TNUM_COUNTER;
const UINT8 tnum_isr2     = TNUM_ISR2;
const UINT8 tnum_resource = TNUM_RESOURCE;
const UINT8 tnum_task     = TNUM_TASK;
const UINT8 tnum_exttask  = TNUM_EXTTASK;

 /****** Object OS ******/

 /****** Object TASK ******/

const TaskType InitializeTask = 0;
const TaskType ControllerTask = 1;
const TaskType DataLoggingTask = 2;
const TaskType AEBTask = 3;
const TaskType ReadRawDataTask = 4;
const TaskType CalculateVehicleSpeedTask = 5;
const TaskType LaneControlTask = 6;
const TaskType AdaptiveCruiseControlTask = 7;
const TaskType SonarTask = 8;

extern void TASKNAME( InitializeTask )( void );
extern void TASKNAME( ControllerTask )( void );
extern void TASKNAME( DataLoggingTask )( void );
extern void TASKNAME( AEBTask )( void );
extern void TASKNAME( ReadRawDataTask )( void );
extern void TASKNAME( CalculateVehicleSpeedTask )( void );
extern void TASKNAME( LaneControlTask )( void );
extern void TASKNAME( AdaptiveCruiseControlTask )( void );
extern void TASKNAME( SonarTask )( void );

static __STK_UNIT _stack_ControllerTask[__TCOUNT_STK_UNIT(512)];
static __STK_UNIT _stack_DataLoggingTask[__TCOUNT_STK_UNIT(512)];
static __STK_UNIT _stack_AEBTask[__TCOUNT_STK_UNIT(512)];
static __STK_UNIT _stack_LaneControlTask[__TCOUNT_STK_UNIT(512)];
static __STK_UNIT _stack_AdaptiveCruiseControlTask[__TCOUNT_STK_UNIT(512)];
static __STK_UNIT _stack_SonarTask[__TCOUNT_STK_UNIT(512)];
static __STK_UNIT _stack_priority_5[__TCOUNT_STK_UNIT(512)];
static __STK_UNIT _stack_priority_6[__TCOUNT_STK_UNIT(512)];

const Priority tinib_inipri[TNUM_TASK] = { TPRI_MINTASK + 6, TPRI_MINTASK + 4, TPRI_MINTASK + 4, TPRI_MINTASK + 2, TPRI_MINTASK + 5, TPRI_MINTASK + 5, TPRI_MINTASK + 3, TPRI_MINTASK + 2, TPRI_MINTASK + 1, };
const Priority tinib_exepri[TNUM_TASK] = { TPRI_MAXTASK, TPRI_MINTASK + 4, TPRI_MINTASK + 4, TPRI_MINTASK + 2, TPRI_MAXTASK, TPRI_MAXTASK, TPRI_MINTASK + 3, TPRI_MINTASK + 2, TPRI_MINTASK + 1, };
const UINT8 tinib_maxact[TNUM_TASK] = { (1) - 1, (1) - 1, (1) - 1, (1) - 1, (1) - 1, (1) - 1, (1) - 1, (1) - 1, (1) - 1, };
const AppModeType tinib_autoact[TNUM_TASK] = { 0x00000001, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, };
const FP tinib_task[TNUM_TASK] = { TASKNAME( InitializeTask ), TASKNAME( ControllerTask ), TASKNAME( DataLoggingTask ), TASKNAME( AEBTask ), TASKNAME( ReadRawDataTask ), TASKNAME( CalculateVehicleSpeedTask ), TASKNAME( LaneControlTask ), TASKNAME( AdaptiveCruiseControlTask ), TASKNAME( SonarTask ), };
const __STK_UNIT tinib_stk[TNUM_TASK] = { (__STK_UNIT)_stack_priority_6, (__STK_UNIT)_stack_ControllerTask, (__STK_UNIT)_stack_DataLoggingTask, (__STK_UNIT)_stack_AEBTask, (__STK_UNIT)_stack_priority_5, (__STK_UNIT)_stack_priority_5, (__STK_UNIT)_stack_LaneControlTask, (__STK_UNIT)_stack_AdaptiveCruiseControlTask, (__STK_UNIT)_stack_SonarTask, };
const UINT16 tinib_stksz[TNUM_TASK] = { 512, 512, 512, 512, 512, 512, 512, 512, 512, };

TaskType tcb_next[TNUM_TASK];
UINT8 tcb_tstat[TNUM_TASK];
Priority tcb_curpri[TNUM_TASK];
UINT8 tcb_actcnt[TNUM_TASK];
EventMaskType tcb_curevt[TNUM_EXTTASK+1];
EventMaskType tcb_waievt[TNUM_EXTTASK+1];
ResourceType tcb_lastres[TNUM_TASK];
DEFINE_CTXB(TNUM_TASK);

 /****** Object COUNTER ******/

const CounterType SysTimerCnt = 0;

const TickType cntinib_maxval[TNUM_COUNTER] = { 10000, };
const TickType cntinib_maxval2[TNUM_COUNTER] = { 20001, };
const TickType cntinib_tickbase[TNUM_COUNTER] = { 1, };
const TickType cntinib_mincyc[TNUM_COUNTER] = { 1, };

AlarmType cntcb_almque[TNUM_COUNTER];
TickType cntcb_curval[TNUM_COUNTER];

 /****** Object ALARM ******/

const AlarmType cyclic_alarm_ControllerTask = 0;
const AlarmType cyclic_alarm_DataloggingTask = 1;
const AlarmType cyclic_alarm_AEBTask = 2;
const AlarmType cyclic_alarm_ReadRawDataTask = 3;
const AlarmType cyclic_alarm_CalculateVehicleSpeedTask = 4;
const AlarmType cyclic_alarm_LaneControlTask = 5;
const AlarmType cyclic_alarm_AdaptiveCruiseControlTask = 6;
const AlarmType cyclic_alarm_SonarTask = 7;

DeclareTask(ControllerTask);
static void _activate_alarm_cyclic_alarm_ControllerTask( void );
static void _activate_alarm_cyclic_alarm_ControllerTask( void )
{ (void)ActivateTask( ControllerTask ); }

DeclareTask(DataLoggingTask);
static void _activate_alarm_cyclic_alarm_DataloggingTask( void );
static void _activate_alarm_cyclic_alarm_DataloggingTask( void )
{ (void)ActivateTask( DataLoggingTask ); }

DeclareTask(AEBTask);
static void _activate_alarm_cyclic_alarm_AEBTask( void );
static void _activate_alarm_cyclic_alarm_AEBTask( void )
{ (void)ActivateTask( AEBTask ); }

DeclareTask(ReadRawDataTask);
static void _activate_alarm_cyclic_alarm_ReadRawDataTask( void );
static void _activate_alarm_cyclic_alarm_ReadRawDataTask( void )
{ (void)ActivateTask( ReadRawDataTask ); }

DeclareTask(CalculateVehicleSpeedTask);
static void _activate_alarm_cyclic_alarm_CalculateVehicleSpeedTask( void );
static void _activate_alarm_cyclic_alarm_CalculateVehicleSpeedTask( void )
{ (void)ActivateTask( CalculateVehicleSpeedTask ); }

DeclareTask(LaneControlTask);
static void _activate_alarm_cyclic_alarm_LaneControlTask( void );
static void _activate_alarm_cyclic_alarm_LaneControlTask( void )
{ (void)ActivateTask( LaneControlTask ); }

DeclareTask(AdaptiveCruiseControlTask);
static void _activate_alarm_cyclic_alarm_AdaptiveCruiseControlTask( void );
static void _activate_alarm_cyclic_alarm_AdaptiveCruiseControlTask( void )
{ (void)ActivateTask( AdaptiveCruiseControlTask ); }

DeclareTask(SonarTask);
static void _activate_alarm_cyclic_alarm_SonarTask( void );
static void _activate_alarm_cyclic_alarm_SonarTask( void )
{ (void)ActivateTask( SonarTask ); }

const CounterType alminib_cntid[TNUM_ALARM] = { 0, 0, 0, 0, 0, 0, 0, 0, };
const FP alminib_cback[TNUM_ALARM] = { _activate_alarm_cyclic_alarm_ControllerTask, _activate_alarm_cyclic_alarm_DataloggingTask, _activate_alarm_cyclic_alarm_AEBTask, _activate_alarm_cyclic_alarm_ReadRawDataTask, _activate_alarm_cyclic_alarm_CalculateVehicleSpeedTask, _activate_alarm_cyclic_alarm_LaneControlTask, _activate_alarm_cyclic_alarm_AdaptiveCruiseControlTask, _activate_alarm_cyclic_alarm_SonarTask, };
const AppModeType alminib_autosta[TNUM_ALARM] = { 0x00000001, 0x00000001, 0x00000001, 0x00000001, 0x00000001, 0x00000001, 0x00000001, 0x00000001, };
const TickType alminib_almval[TNUM_ALARM] = { 1, 1, 1, 1, 1, 1, 1, 1, };
const TickType alminib_cycle[TNUM_ALARM] = { 10, 10, 25, 5, 5, 20, 25, 30, };

AlarmType almcb_next[TNUM_ALARM];
AlarmType almcb_prev[TNUM_ALARM];
TickType almcb_almval[TNUM_ALARM];
TickType almcb_cycle[TNUM_ALARM];

 /****** Object RESOURCE ******/

const ResourceType RES_STEERING_MOTOR = 0;
const ResourceType RES_OVERRIDE_BT = 1;

const Priority resinib_ceilpri[TNUM_RESOURCE] = { TPRI_MINTASK + 4, TPRI_MINTASK + 4, };

Priority rescb_prevpri[TNUM_RESOURCE];
ResourceType rescb_prevres[TNUM_RESOURCE];

 /****** Object EVENT ******/


 /****** Object ISR ******/


#define IPL_MAXISR2 0
const IPL ipl_maxisr2 = IPL_MAXISR2;


const Priority isrinib_intpri[TNUM_ISR2+1] = { 0};
ResourceType isrcb_lastres[TNUM_ISR2+1];

 /****** Object APPMODE ******/

void object_initialize( void )
{
	alarm_initialize();
	resource_initialize();
	task_initialize();
}


/*
 *  TOPPERS/OSEK Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      OSEK Kernel
 * 
 *  Copyright (C) 2006 by Witz Corporation, JAPAN
 * 
 *  ��L���쌠�҂́C�ȉ��� (1)�`(4) �̏������CFree Software Foundation 
 *  �ɂ���Č��\����Ă��� GNU General Public License �� Version 2 �ɋL
 *  �q����Ă�������𖞂����ꍇ�Ɍ���C�{�\�t�g�E�F�A�i�{�\�t�g�E�F�A
 *  �����ς������̂��܂ށD�ȉ������j���g�p�E�����E���ρE�Ĕz�z�i�ȉ��C
 *  ���p�ƌĂԁj���邱�Ƃ𖳏��ŋ�������D
 *  (1) �{�\�t�g�E�F�A���\�[�X�R�[�h�̌`�ŗ��p����ꍇ�ɂ́C��L�̒���
 *      ���\���C���̗��p��������щ��L�̖��ۏ؋K�肪�C���̂܂܂̌`�Ń\�[
 *      �X�R�[�h���Ɋ܂܂�Ă��邱�ƁD
 *  (2) �{�\�t�g�E�F�A���C���C�u�����`���ȂǁC���̃\�t�g�E�F�A�J���Ɏg
 *      �p�ł���`�ōĔz�z����ꍇ�ɂ́C�Ĕz�z�ɔ����h�L�������g�i���p
 *      �҃}�j���A���Ȃǁj�ɁC��L�̒��쌠�\���C���̗��p��������щ��L
 *      �̖��ۏ؋K����f�ڂ��邱�ƁD
 *  (3) �{�\�t�g�E�F�A���C�@��ɑg�ݍ��ނȂǁC���̃\�t�g�E�F�A�J���Ɏg
 *      �p�ł��Ȃ��`�ōĔz�z����ꍇ�ɂ́C���̂����ꂩ�̏����𖞂�����
 *      �ƁD
 *    (a) �Ĕz�z�ɔ����h�L�������g�i���p�҃}�j���A���Ȃǁj�ɁC��L�̒�
 *        �쌠�\���C���̗��p��������щ��L�̖��ۏ؋K����f�ڂ��邱�ƁD
 *    (b) �Ĕz�z�̌`�Ԃ��C�ʂɒ�߂���@�ɂ���āCTOPPERS�v���W�F�N�g��
 *        �񍐂��邱�ƁD
 *  (4) �{�\�t�g�E�F�A�̗��p�ɂ�蒼�ړI�܂��͊ԐړI�ɐ����邢���Ȃ鑹
 *      �Q������C��L���쌠�҂����TOPPERS�v���W�F�N�g��Ɛӂ��邱�ƁD
 * 
 *  �{�\�t�g�E�F�A�́C���ۏ؂Œ񋟂���Ă�����̂ł���D��L���쌠�҂�
 *  ���TOPPERS�v���W�F�N�g�́C�{�\�t�g�E�F�A�Ɋւ��āC���̓K�p�\����
 *  �܂߂āC�����Ȃ�ۏ؂��s��Ȃ��D�܂��C�{�\�t�g�E�F�A�̗��p�ɂ�蒼
 *  �ړI�܂��͊ԐړI�ɐ����������Ȃ鑹�Q�Ɋւ��Ă��C���̐ӔC�𕉂�Ȃ��D
 * 
 */




