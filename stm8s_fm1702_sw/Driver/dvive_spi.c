#include "iostm8s105k6.h"
#include "drive_spi.h"

void drv_spiInit(void)
{
	CLK_PCKENR1 |= 0x02;		/* enable SPI Clock */
	/*
	SPI_CR1：SPI控制寄存器 1
		7：LSBFIRST：帧格式
			0：先发送MSB
			1：先发送LSB
		6：SPE：SPI使能
			0：禁止SPI
			1：开启SPI
		5~3：BR：波特率控制
			000：fMASTER/2
			001：fMASTER/4
			010：fMASTER/8
			011：fMASTER/16
			100：fMASTER/32
			101：fMASTER/64
			110：fMASTER/128
			111：fMASTER/256
    	2：MSTR：主设备选择
			0：配置为从设备
			1：配置为主设备
    	1：CPOL: 时钟极性
			0： 空闲状态时，SCK保持低电平
			1： 空闲状态时，SCK保持高电平
    	0：CPHA: 时钟相位
			0： 数据采样从第一个时钟边沿开始
			1： 数据采样从第二个时钟边沿开始
    */
	SPI_CR1 = 0x1C;
	
	/*
	SPI_CR2：SPI控制寄存器 2
		7：BDM：双向数据模式使能
			0：选择双线单向数据模式
			1：选择单线双向数据模式
		6：BDOE：双向模式下输出使能
			0：输入使能(只接收模式)
			1：输出使能(只发送模式)
		5：CRCEN：硬件CRC计算使能
			0： CRC计算禁止；
			1： CRC计算使能。
			注意：正确的操作是先关闭SPI（ SPE位置0）再写该位
		4：CRCNEXT：接着发送CRC
			0：下一个发送的数据来自Tx缓冲区
			1：下一个发送的数据来自Tx CRC计数器
		3：保留，保持清零
    	2：RXONLY：只接收
			0：全双工(同时发送和接收)
			1：输出禁止(只接收)
    	1：SSM：软件从设备管理
			0：禁止软件从设备管理
			1：使能软件从设备管理
			当该位被置位时， SSI位的值代替NSS引脚的输入控制从设备的选择
    	0：SSI：内部从设备选择
			只有SSM被置位的情况下，该位才有效。 NSS引脚上电平决定于该位的值，而不是NSS引脚上I/O端口的值。
			0：从模式
			1：主模式
    */
	SPI_CR2 = 0x03;
	
	/*
	SPI_ICR：SPI 中断控制寄存器
		7：TXIE： Tx缓冲空中断使能
			0： TXE中断禁止
			1： TXE中断使能
		6：RXIE： Rx缓冲非空中断使能
			0： RxNE中断禁止
			1： RxNE中断使能
		5：ERRIE：错误中断使能
			0：错误中断禁止
			1：错误中断使能
		4：WKIE：唤醒中断使能
			0：唤醒中断禁止
			1：唤醒中断使能
		3~0：保留，强制为0
    */
	SPI_ICR = 0x00;
	
	/*
	SPI_SR：SPI 状态寄存器
		7：BSY：总线忙标志
			0： SPI空闲；
			1： SPI正忙于通信；或者Tx缓冲区非空
		6：OVR：溢出标志
			0：没有发生溢出错误；
			1：发生溢出错误。
		5：MODF：模式错误
			0：没有发生模式错误；
			1：发生模式错误。
		4：CRCERR： CRC错误标志
			0：收到的CRC值和SPI_RXCRCR值匹配；
			1：收到的CRC值和SPI_RXCRCR值不匹配。
		3：WKUP：唤醒标志
			0：没有发生唤醒事件
			1：发生唤醒事件
    	2：保留，强制为0
    	1：TXE: 发送缓冲区空
			0：发送缓冲区非空
			1：发送缓冲区空
    	0：RXNE： 接收缓冲区非空
			0：接收缓冲区空
			1：接收缓冲区非空
    */
	(void)SPI_SR;
	
	(void)SPI_DR;
	
	SPI_CR1 |= 0x40;		/* Enable SPI */
}

UINT8 drv_spiReadWriteByte(UINT8 byte)
{
	while(!(SPI_SR & 0x02));	/* 等待发送寄存器为空 */
	SPI_DR = byte;				/* 将发送的数据写到数据寄存器 */
	while(!(SPI_SR & 0x01));	/* 等待接受寄存器满 */
	return SPI_DR;				/* 读数据寄存器 */
}