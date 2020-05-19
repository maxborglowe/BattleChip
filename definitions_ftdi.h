/* - Definitions for access and usage of the FT812 chip.
	- Here you can find internal adresses and functions that are used to communicate with
	  the built in graphics engine (EVE).
	- If a definition (A) has another indented definition (B) below indicates that (B) is
	  a parameter to (A) */

/* include guard */
#ifndef DEFINITIONS_FTDI_H_
#define DEFINITIONS_FTDI_H_

#define MEM_RD 0x00
#define MEM_WR 0x80

//#######################################
// Data direction and port definition
//#######################################
#define DDR_SPI DDRB
#define PORT_SPI PORTB
	#define SCK PB7
	#define MISO PB6
	#define MOSI PB5
	#define ITR PB3
	#define PDN PB2
	#define SS_LCD PB1
	
#define DDR_BUTTONS DDRA
#define PIN_BUTTONS PINA
	#define BTN_UP PA0
	#define BTN_DN PA1
	#define BTN_L PA2
	#define BTN_R PA3
	#define BTN_SEL PA4

//#######################################
// Adress list
//#######################################
#define RAM_G 0x000000UL			/**General purpose graphics RAM */
#define RAM_DL 0x300000UL			/**Display List RAM, starts at (RAM_DL + 0), increment by 4 in each following wr32 in a single command */
#define RAM_REG 0x302000UL			/**Registers */
#define RAM_CMD 0x308000UL			/**Command buffer (non-display list commands)*/

#define REG_ID 0x302000UL			/** ID register, always reads as 0x7C */
#define REG_CPURESET 0x302020UL		/** Reset control */

#define REG_HCYCLE 0x30202cUL		/**Horizontal total cycle count */
#define REG_HOFFSET 0x30202cUL		/**Horizontal display start offset */
#define REG_HSIZE 0x302034UL		/**Horizontal display pixel count */
#define REG_HSYNC0 0x302038UL		/**Horizontal sync fall offset */
#define REG_HSYNC1 0x30203cUL		/**Horizontal sync rise offset */

#define REG_VCYCLE 0x302040UL		/**Vertical total cycle count */
#define REG_VOFFSET 0x302044UL		/**Vertical display start offset */
#define REG_VSIZE 0x302048UL		/**Vertical display pixel count */
#define REG_VSYNC0 0x30204cUL		/**Vertical sync fall offset */
#define REG_VSYNC1 0x302050UL		/**Vertical sync rise offset */

#define REG_SWIZZLE 0x302064UL		/**Output RGB signal swizzle */
#define REG_PCLK 0x302070UL			/**PCLK frequency divider */
#define REG_PCLK_POL 0x30206cUL		/**PCLK polarity */
#define REG_CSPREAD 0x302068UL		/**O/P clock spreading enable */

#define REG_DLSWAP 0x302054UL		/**Display List swap control, is required to be set to DLSWAP_FRAME 
									   (0x02) to activate new display list on next frame refresh */
#define REG_GPIO_DIR 0x302090UL		/**Legacy GPIO pin direction */
#define REG_GPIO 0x302094UL			/**Legacy GPIO read/write */
#define REG_PWM_HZ 0x3020D0UL		/** Set PWM frequency (250 - 10000Hz) */
#define REG_PWM_DUTY 0x3020D4UL		/** Set PWM strength (0 - 128) */

#define REG_CMD_READ 0x3020F8UL		/** Command buffer read pointer */
#define REG_CMD_WRITE 0x3020fcUL	/** Command buffer write pointer */
#define REG_CMD_DL 0x302100UL		/** Command display list offset */


//#######################################
// Display List commands
//#######################################

/** Specify the alpha test function
   func: specifies test function, with one of the functions below. Init: ALWAYS (7)
   ref: specifies reference value for alpha test. Init: NEVER (0) */
#define ALPHA_FUNC(func, ref) ((9UL<<24)|(((func)&7UL)<<8)|(((ref)&255UL)<<0))
	#define NEVER 0
	#define LESS 1
	#define LEQUAL 2
	#define GREATER 3
	#define GEQUAL 4
	#define EQUAL 5
	#define NOTEQ 6
	#define ALWAYS 7
/** Begin drawing graphics primitive using drawCommands below
   Once primitive is selected, it will be valid till new BEGIN command is executed
   NOTE: Nothing will be drawn until VERTEX2II or VERTEX2F is executed */
#define BEGIN(prim) ((0x1fUL<<24)|(((prim)&15UL)<<0))
	#define BITMAP 1
	#define POINT 2
	#define LINE 3
	#define LINE_STRIP 4
	#define EDGE_STRIP_R 5
	#define EDGE_STRIP_L 6
	#define EDGE_STRIP_A 7
	#define EDGE_STRIP_B 8
	#define RECT 9
#define END() (0x21UL<<24) /** End drawing graphics primitive, recommended to have an END for each BEGIN */
/** Specify pixel arithmetic - Controls how new color values are combined with values in color buffer.
   Given a pixel value source and a previous value in color buffer: source_val * src = destination_val * dst
   for each color channel: r, g, b, and alpha.
   src: How the source blending factor is computed using src commands below. Init: SRC_ALPHA (2)
   dst: How dest. blending factor is computed. Init: ONE_MINUS_SRC_ALPHA (4) */
#define BLEND_FUNC(src, dst) ((0x0bUL<<24)|(((src)&7UL)<<3)|((dst)&7UL))
	#define ZERO 0
	#define ONE 1
	#define SRC_ALPHA 2
	#define DST_ALPHA 3
	#define ONE_MINUS_SRC_ALPHA 4
	#define ONE_MINUS_DST_ALPHA 5
/** Clear buffers to preset values.
   The scissor test and buffer write masks affects operation of CLEAR. Scissor limits cleared rect,
   and buffer write masks limit affected buffers. State of ALPHA_FUNC
   c: HIGH = clear color buffer, s: HIGH = clear stencil buffer, t: HIGH = clear tag buffer */
#define CLEAR(c, s, t) ((0x26UL<<24)|(((c)&1UL)<<2)|(((s)&1UL)<<1)|(((t)&1UL)<<0))
#define CLEAR_COLOR_A(alpha) ((0x0F<<24)|(alpha<<8)) /** Specify clear value for alpha channel, initial value is 0 */
#define CLEAR_COLOR_RGB(red, green, blue) ((2UL<<24)|(((red)&255UL)<<16)|(((green)&255UL)<<8)|(((blue)&255UL)<<0)) /* Sets color values used by a following CLEAR */
#define CLEAR_STENCIL(s) ((0x11UL<<24)|((s)&255UL)) /** Clear value for stencil buffer. s: value to clear stencil buffer. Init: 0 */
#define CLEAR_TAG(t) ((0x12UL<<24)|((t)&255UL)) /** Clear value for tag buffer. s: value to clear tag buffer. Init: 0 */
/** Set alpha value to drawn element (points, lines, bitmaps). How alpha value affects pixels depends on BLEND_FUNC.
  Default behaviour: Transparent blend. 
  alpha: Alpha for current color. Init: 255 */
#define COLOR_A(alpha) ((0x10UL<<24)|((alpha)&255UL))
#define COLOR_RGB(red,green,blue) ((4UL<<24)|(((red)&255UL)<<16)|(((green)&255UL)<<8)|(((blue)&255UL)<<0)) /** Sets color r, g, b. Init (all): 255*/
#define DISPLAY() (0UL<<24) /** Put this at the end of each display list! FT812 will ignore all commands following this command */
/** Set width of drawn line. Width = distance from center to outermost drawn pixel, unit: 1/16 pixel. Range: 0 - 4095, ie 0 - 255 pixels.
	NOTE: Will affect LINES, LINE_STRIP, RECT, EDGE_STRIP_A/B/R/L*/
#define LINE_WIDTH(width) ((0x0eUL<<24)|(((width)&4095UL)<<0))
/** Set point radius. Width = distance from center to outermost drawn pixel, unit: 1/16 pixel. Init: 16. Range: 0 - 8191, ie 0 - 511 pixels.*/
#define POINT_SIZE(p_size) ((0x0dUL<<24)|(((p_size)&8191UL)<<0))
/** Start operation of drawing primitive. Pixel precision & max range of coordinates depends on value of VERTEX_FORMAT.
	x & y: signed coordinates in units of pixel precision defined in command VERTEX_FORMAT. Init: 1/16 pixel precision*/
#define VERTEX2F(x, y) ((1UL<<30)|(((x)&32767UL)<<15)|(((y)&32767UL)<<0))
/** Start operation of drawing primitive.
	x & y: range is 0 - 511 pixels. Init: 1/16 pixel precision*/
#define VERTEX2II(x, y, handle, cell) ((0x2UL<<30)|(((x)&511UL)<<21)|(((y)&511UL)<<12)|(((handle)&31UL)<<7)|(((cell)&127UL)<<0))

//#######################################
// Commands used by coprocessor
//#######################################

#define CMD_SWAP 0xffffff01UL 		/** Co-processor requests DL swap after the current display list has been scanned out */

#define CMD_DLSTART 0xFFFFFF00UL 	/** Tells co-processor to start writing the display list at RAM_DL+0*/

//#######################################
// Commands used by host_command
//#######################################
#define DLSWAP_FRAME 2UL
#define ACTIVE 0x00UL
#define CLKEXT 0x44UL
#define CLKINT 0x48UL
#define CLKSEL 0x61UL
	#define CLK_SPD_DEFAULT 0x00UL

//#######################################
// Parameters to commands used by host_command
//#######################################


#endif /* end of include guard */
