
/* Data direction and ports */
#define DDR_SPI DDRB
#define PORT_SPI PORTB

#define SCK PB7
#define MISO PB6
#define MOSI PB5
#define ITR PB3
#define PDN PB2
#define SS_LCD PB1

#define MEM_RD 0x00
#define MEM_WR 0x80

/* Adress list  */
#define REG_HCYCLE 0x30202cUL		//Horizontal total cycle count
#define REG_HOFFSET 0x30202cUL		//Horizontal display start offset
#define REG_HSIZE 0x302034UL		//Horizontal display pixel count
#define REG_HSYNC0 0x302038UL		//Horizontal sync fall offset
#define REG_HSYNC1 0x30203cUL		//Horizontal sync rise offset

#define REG_VCYCLE 0x302040UL		//Vertical total cycle count
#define REG_VOFFSET 0x302044UL		//Vertical display start offset
#define REG_VSIZE 0x302048UL		//Vertical display pixel count
#define REG_VSYNC0 0x30204cUL		//Vertical sync fall offset
#define REG_VSYNC1 0x302050UL		//Vertical sync rise offset

#define REG_SWIZZLE 0x302064UL		//Output RGB signal swizzle
#define REG_PCLK 0x302070UL			//PCLK frequency divider
#define REG_PCLK_POL 0x30206cUL		//PCLK polarity
#define REG_CSPREAD 0x302068UL		//O/P clock spreading enable

#define RAM_DL 0x300000UL			//Display List RAM
#define REG_DLSWAP 0x302054UL		//Display List swap control
#define REG_GPIO_DIR 0x302090UL		//Legacy GPIO pin direction
#define REG_GPIO 0x302094UL			//Legacy GPIO read/write


#define REG_PWM_HZ 0x3020D0UL	/* Set PWM frequency (250 - 10000Hz) */
#define REG_PWM_DUTY 0x3020D4UL /* Set PWM strength (0 - 128) */

#define DLSWAP_FRAME 2UL
#define DISPLAY() ((0UL<<24))
#define CLEAR(c,s,t) ((38UL<<24)|(((c)&1UL)<<2)|(((s)&1UL)<<1)|(((t)&1UL)<<0))
#define CLEAR_COLOR_RGB(red,green,blue) ((2UL<<24)|(((red)&255UL)<<16)|(((green)&255UL)<<8)|(((blue)&255UL)<<0))


/* Commands used by host_command */
#define ACTIVE 0x00
#define CLKINT 0x48
#define CLKSEL 0x61

/* Parameters to commands */


