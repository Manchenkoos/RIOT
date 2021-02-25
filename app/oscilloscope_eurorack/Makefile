# Name of application
APPLICATION = oscilloscope_eurorack

# If no BOARD is found in the environment, use this default:
BOARD ?= stm32f4discovery

# This has to be the absolute path to the RIOT base directory:
RIOTBASE ?= $(CURDIR)/../..

USEMODULE += ili9341
USEMODULE += xtimer

# Check if being configured via Kconfig
ifndef CONFIG_KCONFIG_USEMODULE_ILI9341
CFLAGS += -DCONFIG_ILI9341_LE_MODE
endif

# Comment this out to disable code in RIOT that does safety checking
# which is not needed in a production environment but helps in the
# development process:
DEVELHELP ?= 1

# Change this to 0 show compiler invocation lines by default:
QUIET ?= 1

include $(RIOTBASE)/Makefile.include


