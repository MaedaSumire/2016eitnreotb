mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))

APPL_COBJS += balancer.o balancer_param.o

APPL_CXXOBJS += \
	MotorDrive.o \
	DeviceValueGet.o \
	UIGet.o \
	RunningData.o \
	PIDCalculation.o \
	RunningDataGet.o \
	RunningCalculation.o \
	RunningController.o \
	SectionDecisionData.o \
	SectionDecisionDataGet.o \
	SectionDecision.o \
	SectionDecisionController.o \
	CompetitionRunning.o \
	ColorGet.o \
	PostureAdjustment.o \
	CalibrationController.o \
	StartInstructionGet.o \
	StartController.o\
	DeviceInterface.o \
	ExtraStageLookUp.o \
	ExtraStageStep.o

SRCLANG := c++

ifdef CONFIG_EV3RT_APPLICATION

# Include libraries
include $(EV3RT_SDK_LIB_DIR)/libcpp-ev3/Makefile

endif

APPL_DIR += $(mkfile_path)CompetitionRunning $(mkfile_path)DeviceAccess $(mkfile_path)Calibration $(mkfile_path)ExtraStage

INCLUDES += \
	-I$(mkfile_path)CompetitionRunning \
	-I$(mkfile_path)DeviceAccess \
	-I$(mkfile_path)Calibration \
	-I$(mkfile_path)ExtraStage

COPTS += -fno-use-cxa-atexit
