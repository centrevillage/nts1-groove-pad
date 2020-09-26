module CppStructSchema
  SCHEMA = 
    {
      GPIO: {
        name: 'GpioInfo',
        attrs: {
          p_gpio: {
            value: nil,
            type: 'GPIO_TypeDef*',
            required: true
          }
        }
      },
      TIM: {
        name: 'TimInfo',
        attrs: {
          category: {
            value: nil,
            type: 'TimCategory',
            required: true
          },
          p_tim: {
            value: nil,
            type: 'TIM_TypeDef*',
            required: true
          },
          irqn: {
            value: nil,
            type: 'IRQn_Type',
            required: true
          }
        }
      },
      RCC: {
        name: 'RccInfo',
        singleton: true,
        attrs: {
          p_rcc: {
            value: nil,
            type: 'RCC_TypeDef*',
            required: true
          }
        }
      },
      I2C: {
        name: 'I2cInfo',
        attrs: {
          p_i2c: {
            value: nil,
            type: 'I2C_TypeDef*',
            required: true
          }
        },
      },
      SPI: {
        name: 'SpiInfo',
        attrs: {
          p_spi: {
            value: nil,
            type: 'SPI_Typedef*',
            required: true
          }
        },
      },
      USART: {
        name: 'UsartInfo',
        attrs: {
          p_usart: {
            value: nil,
            type: 'USART_TypeDef*',
            required: true
          }
        },
      },
      DAC: {
        name: 'DacInfo',
        attrs: {
          p_dac: {
            value: nil,
            type: 'DAC_TypeDef*',
            required: true
          }
        }
      },
      ADC: {
        name: 'AdcInfo',
        attrs: {
          p_adc: {
            value: nil,
            type: 'ADC_TypeDef*',
            required: true
          },
        }
      },
      TSC: {
        name: 'TscInfo',
        singleton: true,
        attrs: {
          p_tsc: {
            value: nil,
            type: 'TSC_TypeDef*'
          }
        }
      },
      # 下記は未サポート
      #FLASH: {
      #  name: 'FLASHCtrl',
      #  attrs: {
      #    p_flash: {
      #      value: nil,
      #      type: 'FLASH_TypeDef*',
      #      required: true
      #    }
      #  }
      #},
      #EXTI: {
      #  name: 'EXTICtrl',
      #  attrs: {
      #    p_exti: {
      #      value: nil,
      #      type: 'EXTI_TypeDef*',
      #      required: true
      #    }
      #  }
      #},
      #NVIC: {
      #  name: 'NVICCtrl',
      #  attrs: {}
      #},
      #SAI: {
      #  name: 'SAICh',
      #  attrs: {
      #    p_sai: {
      #      value: nil,
      #      type: 'SAI_TypeDef*',
      #      required: true
      #    },
      #    p_sai_a: {
      #      value: nil,
      #      type: 'SAI_Block_TypeDef*',
      #      required: true
      #    },
      #    p_sai_b: {
      #      value: nil,
      #      type: 'SAI_Block_TypeDef*',
      #      required: true
      #    },
      #  }
      #},
      # DMA: { # Port と Ch に分ける？
      #   name: 'DMACh',
      #   attrs: {
      #     p_dma: {
      #       value: nil,
      #       type: 'DMA_TypeDef*',
      #       required: true
      #     },
      #     p_dma_ch: {
      #       value: nil,
      #       type: 'DMA_Channel_TypeDef*',
      #       required: true
      #     }
      #   }
      # },
      # FSMC: {
      #   name: 'FSMCCtrl'
      # },
      #PWR: {},
      #AFIO: {},
      #RTC: {},
      #BKP: {},
      #IWDG: {},
      #WWDG: {},
      #DBG: {},
      #CRC: {},
      #CEC: {},
      #COMP1: {},
      #CRS: {},
      #BDMA: {},
      #DMA2D: {},
      #DMAMUX: {},
      #FMC: {},
      #HSEM: {},
      #JPEG: {},
      #MDMA: {},
      #QUADSPI: {},
      #RNG: {},
      #SDMMC: {},
      #VREFBUF: {},
      #LTDC: {},
      #SPDIFRX: {},
      #LPTIM: {},
      #LPUART: {},
      #SYSCFG: {},
      #DLYB: {},
      #Flash: {},
      #AXI: {},
      #DCMI: {},
      #USB_OTG_HS: {},
      #Ethernet: {},
      #HRTIM: {},
      #DFSDM: {},
      #TIMs: {},
      #FDCAN: {},
      #MDIOS: {},
      #OPAMP: {},
      #SWPMI: {},
      #MPU: {},
      #STK: {},
      #FPU: {},
      #SCB: {},
      #PF: {},
      #AC: {},
      #DBGMCU: {},
      #COMP: {},
      #FMAC: {},
      #CORDIC: {},
      #TAMP: {},
      #UCPD: {},
      #USB: {},
      #AES: {},
      #TSC: {},
      #CAN: {},
      #USB_FS: {},
      #SYSCFG_COMP_OPAMP: {},
      #ADC_Common: {},
      #SDIO: {},
      #USB_OTG_FS: {},
      #USBPHYC: {},
      #HASH: {},
      #CRYP: {},
      #SDADC: {},
      #DAC2: {},
      #USB_OTG: {},
      #SAI1: {},
      #SPDIF_RX: {},
      #DSI: {},
      #ETHERNET: {},
      #OctoSPI: {},
      #:"OctoSPII/O": {},
      #Manager: {},
      #OTFDEC: {},
      #RAMECC: {},
      #ART: {},
      #DSIHOST: {},
      #HDMI_CEC: {}
    }.freeze

  GPIO_AF_SCHEMA = {
    SPI: {
      name: 'GpioAfInfo',
      attrs: {
        p_gpio: {
          value: nil,
          type: 'GPIO_TypeDef*',
        },
        pin_bit: {
          value: nil,
          type: 'uint16_t',
        },
        af_idx: {
          value: nil,
          type: 'uint8_t',
        }
      },
    },
  }.freeze

  def self.create(group_name)
    Marshal.load(Marshal.dump(SCHEMA[group_name.to_sym]))
  end

  def self.create_gpio_af(group_name)
    Marshal.load(Marshal.dump(GPIO_AF_SCHEMA[group_name.to_sym]))
  end
end
