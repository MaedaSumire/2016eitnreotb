mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))

APPL_COBJS += balancer.o balancer_param.o

APPL_CXXOBJS += \
	DeviceValueGet.o \
	MotorDrive.o \
	RunningData.o \
	PIDCalculation.o \
	RunningDataGet.o \
	RunningCalculation.o \
	RunningController.o \
	SectionDecisionData.o \
	SectionDecisionDataGet.o \
	SectionDecision.o \
	SectionDecisionController.o \
	CompetitionRunning.o


SRCLANG := c++

ifdef CONFIG_EV3RT_APPLICATION

# Include libraries
include $(EV3RT_SDK_LIB_DIR)/libcpp-ev3/Makefile

endif

APPL_DIR += $(mkfile_path)CompetitionRunning $(mkfile_path)DeviceAccess

INCLUDES += \
	-I$(mkfile_path)CompetitionRunning \
	-I$(mkfile_path)DeviceAccess

COPTS += -fno-use-cxa-atexit
