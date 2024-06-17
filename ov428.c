#include <linux/module.h>
#include <linux/i2c.h>
#include <linux/v4l2-subdev.h>

#include <asm/unaligned.h>
 
#include <linux/clk.h>
#include <linux/delay.h>
#include <linux/i2c.h>
#include <linux/module.h>
#include <linux/pm_runtime.h>
 
#include <media/v4l2-ctrls.h>
#include <media/v4l2-fwnode.h>
#include <media/v4l2-subdev.h>

static int ov428_write_register(struct i2c_client *client, u16 reg, u8 value) {
    int ret;
    u8 buf[3] = {reg >> 8, reg & 0xFF, value};
    ret = i2c_master_send(client, buf, 3);
    if (ret < 0) {
        dev_err(&client->dev, "Failed to write reg 0x%04x, error %d\\n", reg, ret);
    }
    return ret;
}

static int ov428_set_mode(struct i2c_client *client) {
    int ret = 0;

    // Software reset
    ret |= ov428_write_register(client, 0x0103, 0x01);
    msleep(10); // Delay for reset

    // Clock and timing settings
    ret |= ov428_write_register(client, 0x0301, 0xc8);
    ret |= ov428_write_register(client, 0x0304, 0x01);
    ret |= ov428_write_register(client, 0x0305, 0xc4);
    ret |= ov428_write_register(client, 0x0306, 0x04);
    ret |= ov428_write_register(client, 0x0307, 0x00);
    ret |= ov428_write_register(client, 0x0324, 0x01);
    ret |= ov428_write_register(client, 0x0325, 0x90);
    ret |= ov428_write_register(client, 0x032a, 0x09);
    ret |= ov428_write_register(client, 0x032b, 0x00);
    ret |= ov428_write_register(client, 0x032e, 0x00);
    ret |= ov428_write_register(client, 0x3001, 0x20);
    ret |= ov428_write_register(client, 0x300d, 0x00);
    ret |= ov428_write_register(client, 0x3031, 0x02);
    ret |= ov428_write_register(client, 0x3106, 0x20);
    ret |= ov428_write_register(client, 0x3501, 0x00);
    ret |= ov428_write_register(client, 0x3502, 0x04);
    ret |= ov428_write_register(client, 0x3503, 0xaa);
    ret |= ov428_write_register(client, 0x3508, 0x01);
    ret |= ov428_write_register(client, 0x3509, 0x00);
    ret |= ov428_write_register(client, 0x3523, 0x03);
    ret |= ov428_write_register(client, 0x3524, 0x0f);
    ret |= ov428_write_register(client, 0x3541, 0x00);
    ret |= ov428_write_register(client, 0x3542, 0x04);
    ret |= ov428_write_register(client, 0x3543, 0xaa);
    ret |= ov428_write_register(client, 0x3548, 0x01);
    ret |= ov428_write_register(client, 0x3549, 0x00);
    ret |= ov428_write_register(client, 0x3563, 0x03);
    ret |= ov428_write_register(client, 0x3564, 0x0f);
    ret |= ov428_write_register(client, 0x3600, 0x00);
    ret |= ov428_write_register(client, 0x3601, 0x00);
    ret |= ov428_write_register(client, 0x360f, 0x80);
    ret |= ov428_write_register(client, 0x3610, 0x2b);
    ret |= ov428_write_register(client, 0x3617, 0x08);
    ret |= ov428_write_register(client, 0x3631, 0xb9);
    ret |= ov428_write_register(client, 0x3660, 0x02);
    ret |= ov428_write_register(client, 0x3663, 0x00);
    ret |= ov428_write_register(client, 0x3665, 0x15);
    ret |= ov428_write_register(client, 0x3668, 0x0c);
    ret |= ov428_write_register(client, 0x3701, 0x00);
    ret |= ov428_write_register(client, 0x3737, 0xc0);
    ret |= ov428_write_register(client, 0x3820, 0x00);
    ret |= ov428_write_register(client, 0x3821, 0x02);
    ret |= ov428_write_register(client, 0x3822, 0x00);
    ret |= ov428_write_register(client, 0x3823, 0x02);
    ret |= ov428_write_register(client, 0x3824, 0x05);
    ret |= ov428_write_register(client, 0x3825, 0xe9);
    ret |= ov428_write_register(client, 0x3826, 0x05);
    ret |= ov428_write_register(client, 0x3827, 0xe9);
    ret |= ov428_write_register(client, 0x3828, 0x05);
    ret |= ov428_write_register(client, 0x3829, 0xdc);
    ret |= ov428_write_register(client, 0x382a, 0x05);
    ret |= ov428_write_register(client, 0x382b, 0xdc);
    ret |= ov428_write_register(client, 0x382c, 0x06);
    ret |= ov428_write_register(client, 0x382d, 0x68);
    ret |= ov428_write_register(client, 0x382e, 0x06);
    ret |= ov428_write_register(client, 0x382f, 0x5a);
    ret |= ov428_write_register(client, 0x3831, 0x06);
    ret |= ov428_write_register(client, 0x3833, 0x06);
    ret |= ov428_write_register(client, 0x3840, 0x00);
    ret |= ov428_write_register(client, 0x3856, 0x16);
    ret |= ov428_write_register(client, 0x3a02, 0x0f);
    ret |= ov428_write_register(client, 0x3a03, 0xe0);
    ret |= ov428_write_register(client, 0x3a05, 0x30);
    ret |= ov428_write_register(client, 0x3a0a, 0x00);
    ret |= ov428_write_register(client, 0x3a0b, 0x7f);
    ret |= ov428_write_register(client, 0x3a0d, 0x04);
    ret |= ov428_write_register(client, 0x3a18, 0x07);
    ret |= ov428_write_register(client, 0x3a19, 0xff);
    ret |= ov428_write_register(client, 0x3b02, 0x00);
    ret |= ov428_write_register(client, 0x3b03, 0x00);
    ret |= ov428_write_register(client, 0x3b05, 0x30);
    ret |= ov428_write_register(client, 0x3b0a, 0x00);
    ret |= ov428_write_register(client, 0x3b0b, 0x7f);
    ret |= ov428_write_register(client, 0x3b0d, 0x04);
    ret |= ov428_write_register(client, 0x3b18, 0x07);
    ret |= ov428_write_register(client, 0x3b19, 0xff);
    ret |= ov428_write_register(client, 0x3f00, 0x09);
    ret |= ov428_write_register(client, 0x3f05, 0xe0);
    ret |= ov428_write_register(client, 0x3f0a, 0x00);
    ret |= ov428_write_register(client, 0x3f0c, 0x00);
    ret |= ov428_write_register(client, 0x3f0d, 0x56);
    ret |= ov428_write_register(client, 0x3f0e, 0x64);
    ret |= ov428_write_register(client, 0x4009, 0x01);
    ret |= ov428_write_register(client, 0x400d, 0x01);
    ret |= ov428_write_register(client, 0x4480, 0x02);
    ret |= ov428_write_register(client, 0x480e, 0x00);
    ret |= ov428_write_register(client, 0x4813, 0xe4);
    ret |= ov428_write_register(client, 0x4827, 0x55);
    ret |= ov428_write_register(client, 0x4837, 0x08);
    ret |= ov428_write_register(client, 0x4b02, 0x28);
    ret |= ov428_write_register(client, 0x4b03, 0x90);
    ret |= ov428_write_register(client, 0x4b04, 0x00);
    ret |= ov428_write_register(client, 0x4b05, 0x07);
    ret |= ov428_write_register(client, 0x4b08, 0x7f);
    ret |= ov428_write_register(client, 0x4b0e, 0x8f);
    ret |= ov428_write_register(client, 0x4b0f, 0x28);
    ret |= ov428_write_register(client, 0x4b10, 0x60);
    ret |= ov428_write_register(client, 0x4b11, 0x60);
    ret |= ov428_write_register(client, 0x4b12, 0x02);
    ret |= ov428_write_register(client, 0x4b13, 0x01);
    ret |= ov428_write_register(client, 0x4b14, 0x01);
    ret |= ov428_write_register(client, 0x4b15, 0x01);
    ret |= ov428_write_register(client, 0x4b16, 0x01);
    ret |= ov428_write_register(client, 0x4b17, 0x01);
    ret |= ov428_write_register(client, 0x4b1c, 0x02);
    ret |= ov428_write_register(client, 0x4b1d, 0x1e);
    ret |= ov428_write_register(client, 0x4b1e, 0x01);
    ret |= ov428_write_register(client, 0x4b1f, 0x02);
    ret |= ov428_write_register(client, 0x4b20, 0x01);
    ret |= ov428_write_register(client, 0x4b21, 0x02);
    ret |= ov428_write_register(client, 0x4b22, 0x02);
    ret |= ov428_write_register(client, 0x4b23, 0x02);
    ret |= ov428_write_register(client, 0x4b24, 0x01);
    ret |= ov428_write_register(client, 0x4b26, 0xa1);
    ret |= ov428_write_register(client, 0x4b27, 0x01);
    ret |= ov428_write_register(client, 0x4b29, 0x01);
    ret |= ov428_write_register(client, 0x4b2b, 0x0e);
    ret |= ov428_write_register(client, 0x4b2c, 0x01);
    ret |= ov428_write_register(client, 0x4b2d, 0x0a);
    ret |= ov428_write_register(client, 0x4b34, 0xd0);
    ret |= ov428_write_register(client, 0x4b35, 0xaf);
    ret |= ov428_write_register(client, 0x4b36, 0x80);
    ret |= ov428_write_register(client, 0x4b3d, 0x00);
    ret |= ov428_write_register(client, 0x4b48, 0xbb);
    ret |= ov428_write_register(client, 0x4b49, 0x01);
    ret |= ov428_write_register(client, 0x4f01, 0x12);
    ret |= ov428_write_register(client, 0x5004, 0x94);
    ret |= ov428_write_register(client, 0x5005, 0x00);
    ret |= ov428_write_register(client, 0x500e, 0x00);
    ret |= ov428_write_register(client, 0x5044, 0x06);
    ret |= ov428_write_register(client, 0x5045, 0x06);
    ret |= ov428_write_register(client, 0x5046, 0x04);
    ret |= ov428_write_register(client, 0x5047, 0x02);
    ret |= ov428_write_register(client, 0x5048, 0x05);
    ret |= ov428_write_register(client, 0x5049, 0xdc);
    ret |= ov428_write_register(client, 0x504a, 0x05);
    ret |= ov428_write_register(client, 0x504b, 0xdc);
    ret |= ov428_write_register(client, 0x504c, 0x02);
    ret |= ov428_write_register(client, 0x504d, 0xd0);
    ret |= ov428_write_register(client, 0x504e, 0x02);
    ret |= ov428_write_register(client, 0x504f, 0xd0);
    ret |= ov428_write_register(client, 0x5070, 0x04);
    ret |= ov428_write_register(client, 0x5071, 0x02);
    ret |= ov428_write_register(client, 0x5072, 0x04);
    ret |= ov428_write_register(client, 0x5073, 0x02);
    ret |= ov428_write_register(client, 0x5074, 0x02);
    ret |= ov428_write_register(client, 0x5075, 0xd0);
    ret |= ov428_write_register(client, 0x5076, 0x02);
    ret |= ov428_write_register(client, 0x5077, 0xd0);
    ret |= ov428_write_register(client, 0x5078, 0x02);
    ret |= ov428_write_register(client, 0x5079, 0xd0);
    ret |= ov428_write_register(client, 0x507a, 0x02);
    ret |= ov428_write_register(client, 0x507b, 0xd0);
    ret |= ov428_write_register(client, 0x5140, 0x00);
    ret |= ov428_write_register(client, 0x5141, 0x00);
    ret |= ov428_write_register(client, 0x5148, 0x05);
    ret |= ov428_write_register(client, 0x5149, 0xdc);
    ret |= ov428_write_register(client, 0x514a, 0x05);
    ret |= ov428_write_register(client, 0x514b, 0xdc);
    ret |= ov428_write_register(client, 0x5240, 0x33);
    ret |= ov428_write_register(client, 0x5440, 0x00);
    ret |= ov428_write_register(client, 0x5441, 0x00);
    ret |= ov428_write_register(client, 0x3408, 0x0d);
    ret |= ov428_write_register(client, 0x4b03, 0xd0);
    ret |= ov428_write_register(client, 0x4b0e, 0x8d);
    ret |= ov428_write_register(client, 0x3408, 0x1d);
    ret |= ov428_write_register(client, 0x3408, 0xad);
    ret |= ov428_write_register(client, 0x4b00, 0x00);
    ret |= ov428_write_register(client, 0xc289, 0x20);
    ret |= ov428_write_register(client, 0xc28d, 0x10);
    ret |= ov428_write_register(client, 0xb208, 0x05);
    ret |= ov428_write_register(client, 0xb800, 0x14);
    ret |= ov428_write_register(client, 0xb87e, 0x02);
    ret |= ov428_write_register(client, 0xb501, 0x02);
    ret |= ov428_write_register(client, 0xb508, 0x02);
    ret |= ov428_write_register(client, 0xb541, 0x02);
    ret |= ov428_write_register(client, 0xb548, 0x02);
    ret |= ov428_write_register(client, 0xb581, 0x02);
    ret |= ov428_write_register(client, 0xb588, 0x02);
    ret |= ov428_write_register(client, 0xb208, 0x15);
    ret |= ov428_write_register(client, 0xb03a, 0x13);
    ret |= ov428_write_register(client, 0x8301, 0xc8);
    ret |= ov428_write_register(client, 0x8302, 0x31);
    ret |= ov428_write_register(client, 0x8304, 0x01);
    ret |= ov428_write_register(client, 0x8305, 0xf4);
    ret |= ov428_write_register(client, 0x8307, 0x00);
    ret |= ov428_write_register(client, 0x8309, 0x50);
    ret |= ov428_write_register(client, 0x830a, 0x00);
    ret |= ov428_write_register(client, 0x8320, 0x0a);
    ret |= ov428_write_register(client, 0x8324, 0x02);
    ret |= ov428_write_register(client, 0x8325, 0x30);
    ret |= ov428_write_register(client, 0x8326, 0xcd);
    ret |= ov428_write_register(client, 0x8327, 0x06);
    ret |= ov428_write_register(client, 0x8329, 0x00);
    ret |= ov428_write_register(client, 0x832a, 0x06);
    ret |= ov428_write_register(client, 0x832b, 0x00);
    ret |= ov428_write_register(client, 0x832f, 0xc1);
    ret |= ov428_write_register(client, 0x8321, 0x01);
    ret |= ov428_write_register(client, 0xb63b, 0x0e);
    ret |= ov428_write_register(client, 0x8360, 0x01);
    ret |= ov428_write_register(client, 0xb01b, 0xf0);
    ret |= ov428_write_register(client, 0xb020, 0x99);
    ret |= ov428_write_register(client, 0xb022, 0x09);
    ret |= ov428_write_register(client, 0xb026, 0xb4);
    ret |= ov428_write_register(client, 0xb027, 0xf1);
    ret |= ov428_write_register(client, 0xb038, 0x02);
    ret |= ov428_write_register(client, 0xb03f, 0x03);
    ret |= ov428_write_register(client, 0xb216, 0x31);
    ret |= ov428_write_register(client, 0xb218, 0x24);
    ret |= ov428_write_register(client, 0xb501, 0x00);
    ret |= ov428_write_register(client, 0xb502, 0x80);
    ret |= ov428_write_register(client, 0xb541, 0x00);
    ret |= ov428_write_register(client, 0xb542, 0x40);
    ret |= ov428_write_register(client, 0xb504, 0xc8);
    ret |= ov428_write_register(client, 0xb507, 0x00);
    ret |= ov428_write_register(client, 0xb508, 0x01);
    ret |= ov428_write_register(client, 0xb509, 0x00);
    ret |= ov428_write_register(client, 0xb50a, 0x01);
    ret |= ov428_write_register(client, 0xb50b, 0x00);
    ret |= ov428_write_register(client, 0xb50c, 0x00);
    ret |= ov428_write_register(client, 0xb544, 0x48);
    ret |= ov428_write_register(client, 0xb548, 0x01);
    ret |= ov428_write_register(client, 0xb549, 0x00);
    ret |= ov428_write_register(client, 0xb54a, 0x01);
    ret |= ov428_write_register(client, 0xb54b, 0x00);
    ret |= ov428_write_register(client, 0xb54c, 0x00);
    ret |= ov428_write_register(client, 0xb600, 0x82);
    ret |= ov428_write_register(client, 0xb601, 0x38);
    ret |= ov428_write_register(client, 0xb603, 0x08);
    ret |= ov428_write_register(client, 0xb610, 0x57);
    ret |= ov428_write_register(client, 0xb613, 0x78);
    ret |= ov428_write_register(client, 0xb623, 0x00);
    ret |= ov428_write_register(client, 0xb641, 0x00);
    ret |= ov428_write_register(client, 0xb642, 0x00);
    ret |= ov428_write_register(client, 0xb645, 0x80);
    ret |= ov428_write_register(client, 0xb64c, 0x70);
    ret |= ov428_write_register(client, 0xb64d, 0x37);
    ret |= ov428_write_register(client, 0xb65e, 0x02);
    ret |= ov428_write_register(client, 0xb65f, 0x0f);
    ret |= ov428_write_register(client, 0xb700, 0x29);
    ret |= ov428_write_register(client, 0xb701, 0x0d);
    ret |= ov428_write_register(client, 0xb702, 0x3c);
    ret |= ov428_write_register(client, 0xb703, 0x12);
    ret |= ov428_write_register(client, 0xb704, 0x07);
    ret |= ov428_write_register(client, 0xb705, 0x00);
    ret |= ov428_write_register(client, 0xb706, 0x24);
    ret |= ov428_write_register(client, 0xb707, 0x08);
    ret |= ov428_write_register(client, 0xb708, 0x31);
    ret |= ov428_write_register(client, 0xb709, 0x40);
    ret |= ov428_write_register(client, 0xb70a, 0x00);
    ret |= ov428_write_register(client, 0xb70b, 0x4a);
    ret |= ov428_write_register(client, 0xb70c, 0x11);
    ret |= ov428_write_register(client, 0xb712, 0x51);
    ret |= ov428_write_register(client, 0xb714, 0x24);
    ret |= ov428_write_register(client, 0xb717, 0x01);
    ret |= ov428_write_register(client, 0xb71d, 0x20);
    ret |= ov428_write_register(client, 0xb71f, 0x09);
    ret |= ov428_write_register(client, 0xb737, 0x08);
    ret |= ov428_write_register(client, 0xb739, 0x28);
    ret |= ov428_write_register(client, 0xb7e3, 0x08);
    ret |= ov428_write_register(client, 0xb760, 0x08);
    ret |= ov428_write_register(client, 0xb761, 0x0c);
    ret |= ov428_write_register(client, 0xb762, 0x08);
    ret |= ov428_write_register(client, 0xb763, 0x04);
    ret |= ov428_write_register(client, 0xb764, 0x04);
    ret |= ov428_write_register(client, 0xb765, 0x08);
    ret |= ov428_write_register(client, 0xb766, 0x10);
    ret |= ov428_write_register(client, 0xb767, 0x08);
    ret |= ov428_write_register(client, 0xb768, 0x04);
    ret |= ov428_write_register(client, 0xb769, 0x1c);
    ret |= ov428_write_register(client, 0xb76c, 0x00);
    ret |= ov428_write_register(client, 0xb791, 0x24);
    ret |= ov428_write_register(client, 0xb79b, 0x4e);
    ret |= ov428_write_register(client, 0xb7ae, 0x00);
    ret |= ov428_write_register(client, 0xb7e6, 0x08);
    ret |= ov428_write_register(client, 0xb7cb, 0x03);
    ret |= ov428_write_register(client, 0xb7cc, 0x01);
    ret |= ov428_write_register(client, 0xb800, 0x00);
    ret |= ov428_write_register(client, 0xb801, 0x00);
    ret |= ov428_write_register(client, 0xb802, 0x00);
    ret |= ov428_write_register(client, 0xb803, 0x00);
    ret |= ov428_write_register(client, 0xb804, 0x05);
    ret |= ov428_write_register(client, 0xb805, 0xeb);
    ret |= ov428_write_register(client, 0xb806, 0x05);
    ret |= ov428_write_register(client, 0xb807, 0xeb);
    ret |= ov428_write_register(client, 0xb808, 0x05);
    ret |= ov428_write_register(client, 0xb809, 0xec);
    ret |= ov428_write_register(client, 0xb80a, 0x05);
    ret |= ov428_write_register(client, 0xb80b, 0xe8);
    ret |= ov428_write_register(client, 0xb80c, 0x03);
    ret |= ov428_write_register(client, 0xb80d, 0x34);
    ret |= ov428_write_register(client, 0xb80e, 0x06);
    ret |= ov428_write_register(client, 0xb80f, 0x5a);
    ret |= ov428_write_register(client, 0xb810, 0x00);
    ret |= ov428_write_register(client, 0xb811, 0x00);
    ret |= ov428_write_register(client, 0xb812, 0x00);
    ret |= ov428_write_register(client, 0xb813, 0x02);
    ret |= ov428_write_register(client, 0xb814, 0x11);
    ret |= ov428_write_register(client, 0xb815, 0x11);
    ret |= ov428_write_register(client, 0xb81a, 0x0c);
    ret |= ov428_write_register(client, 0xb81b, 0x9e);
    ret |= ov428_write_register(client, 0xb81f, 0x08);
    ret |= ov428_write_register(client, 0xb820, 0x80);
    ret |= ov428_write_register(client, 0xb821, 0x02);
    ret |= ov428_write_register(client, 0xb822, 0x80);
    ret |= ov428_write_register(client, 0xb823, 0x04);
    ret |= ov428_write_register(client, 0xb82d, 0x00);
    ret |= ov428_write_register(client, 0xb82e, 0x00);
    ret |= ov428_write_register(client, 0xb831, 0x00);
    ret |= ov428_write_register(client, 0xb837, 0x07);
    ret |= ov428_write_register(client, 0xb83f, 0x40);
    ret |= ov428_write_register(client, 0xb86b, 0x04);
    ret |= ov428_write_register(client, 0xb871, 0x28);
    ret |= ov428_write_register(client, 0xb894, 0x00);
    ret |= ov428_write_register(client, 0xb94b, 0x0a);
    ret |= ov428_write_register(client, 0xb94c, 0x0a);
    ret |= ov428_write_register(client, 0xb94d, 0x0a);
    ret |= ov428_write_register(client, 0xb94e, 0x0a);
    ret |= ov428_write_register(client, 0xb94f, 0x01);
    ret |= ov428_write_register(client, 0xb950, 0x01);
    ret |= ov428_write_register(client, 0xb951, 0x01);
    ret |= ov428_write_register(client, 0xb952, 0x01);
    ret |= ov428_write_register(client, 0xb953, 0x01);
    ret |= ov428_write_register(client, 0xb954, 0x01);
    ret |= ov428_write_register(client, 0xb955, 0x01);
    ret |= ov428_write_register(client, 0xb956, 0x01);
    ret |= ov428_write_register(client, 0xb957, 0x10);
    ret |= ov428_write_register(client, 0xb958, 0x0e);
    ret |= ov428_write_register(client, 0xb959, 0x0e);
    ret |= ov428_write_register(client, 0xb95a, 0x0e);
    ret |= ov428_write_register(client, 0xb95b, 0x12);
    ret |= ov428_write_register(client, 0xb95c, 0x09);
    ret |= ov428_write_register(client, 0xb95d, 0x05);
    ret |= ov428_write_register(client, 0xb95e, 0x03);
    ret |= ov428_write_register(client, 0xb95f, 0x00);
    ret |= ov428_write_register(client, 0xb960, 0x00);
    ret |= ov428_write_register(client, 0xb961, 0x00);
    ret |= ov428_write_register(client, 0xb962, 0x00);
    ret |= ov428_write_register(client, 0xb963, 0x00);
    ret |= ov428_write_register(client, 0xb964, 0x00);
    ret |= ov428_write_register(client, 0xb965, 0x00);
    ret |= ov428_write_register(client, 0xb966, 0x00);
    ret |= ov428_write_register(client, 0xb967, 0x00);
    ret |= ov428_write_register(client, 0xb968, 0x01);
    ret |= ov428_write_register(client, 0xb969, 0x01);
    ret |= ov428_write_register(client, 0xb96a, 0x01);
    ret |= ov428_write_register(client, 0xb96b, 0x01);
    ret |= ov428_write_register(client, 0xb96c, 0x10);
    ret |= ov428_write_register(client, 0xb96f, 0x00);
    ret |= ov428_write_register(client, 0xb970, 0x2c);
    ret |= ov428_write_register(client, 0xb971, 0x2c);
    ret |= ov428_write_register(client, 0xb972, 0x2c);
    ret |= ov428_write_register(client, 0xb973, 0x10);
    ret |= ov428_write_register(client, 0xb974, 0x00);
    ret |= ov428_write_register(client, 0xb975, 0x31);
    ret |= ov428_write_register(client, 0xb976, 0x31);
    ret |= ov428_write_register(client, 0xb977, 0x31);
    ret |= ov428_write_register(client, 0xb978, 0x12);
    ret |= ov428_write_register(client, 0xb9b1, 0x01);
    ret |= ov428_write_register(client, 0xb9be, 0x00);
    ret |= ov428_write_register(client, 0xb400, 0x08);
    ret |= ov428_write_register(client, 0xb421, 0x00);
    ret |= ov428_write_register(client, 0xb422, 0x06);
    ret |= ov428_write_register(client, 0xb424, 0x00);
    ret |= ov428_write_register(client, 0xb426, 0x00);
    ret |= ov428_write_register(client, 0xb427, 0x00);
    ret |= ov428_write_register(client, 0xbf00, 0x10);
    ret |= ov428_write_register(client, 0xbd85, 0x0b);
    ret |= ov428_write_register(client, 0xbd8c, 0x70);
    ret |= ov428_write_register(client, 0xbd8d, 0x79);
    ret |= ov428_write_register(client, 0xd112, 0x00);
    ret |= ov428_write_register(client, 0xbdaa, 0x00);
    ret |= ov428_write_register(client, 0xbdab, 0x10);
    ret |= ov428_write_register(client, 0xbdae, 0x00);
    ret |= ov428_write_register(client, 0xbdaf, 0x6f);
    ret |= ov428_write_register(client, 0xc000, 0xf8);
    ret |= ov428_write_register(client, 0xc001, 0xeb);
    ret |= ov428_write_register(client, 0xc002, 0x00);
    ret |= ov428_write_register(client, 0xc003, 0x10);
    ret |= ov428_write_register(client, 0xc008, 0x00);
    ret |= ov428_write_register(client, 0xc009, 0x0f);
    ret |= ov428_write_register(client, 0xc00a, 0x00);
    ret |= ov428_write_register(client, 0xc00b, 0x17);
    ret |= ov428_write_register(client, 0xc00c, 0x00);
    ret |= ov428_write_register(client, 0xc00d, 0xa8);
    ret |= ov428_write_register(client, 0xc00e, 0x04);
    ret |= ov428_write_register(client, 0xc00f, 0xd1);
    ret |= ov428_write_register(client, 0xc017, 0x02);
    ret |= ov428_write_register(client, 0xc288, 0xc7);
    ret |= ov428_write_register(client, 0xc29f, 0x00);
    ret |= ov428_write_register(client, 0xc2a0, 0x31);
    ret |= ov428_write_register(client, 0xc80e, 0x00);
    ret |= ov428_write_register(client, 0xc837, 0x10);
    ret |= ov428_write_register(client, 0xc850, 0x42);
    ret |= ov428_write_register(client, 0xc883, 0x02);
    ret |= ov428_write_register(client, 0xc885, 0x14);
    ret |= ov428_write_register(client, 0xc88b, 0x03);
    ret |= ov428_write_register(client, 0xcb00, 0x2a);
    ret |= ov428_write_register(client, 0xcb0d, 0x00);
    ret |= ov428_write_register(client, 0xc500, 0x50);
    ret |= ov428_write_register(client, 0xc501, 0x00);
    ret |= ov428_write_register(client, 0xc502, 0x20);
    ret |= ov428_write_register(client, 0xc503, 0x00);
    ret |= ov428_write_register(client, 0xc504, 0x00);
    ret |= ov428_write_register(client, 0xc505, 0x00);
    ret |= ov428_write_register(client, 0xc508, 0x00);
    ret |= ov428_write_register(client, 0xc50a, 0x04);
    ret |= ov428_write_register(client, 0xc50c, 0x00);
    ret |= ov428_write_register(client, 0xc50e, 0x00);
    ret |= ov428_write_register(client, 0xc50f, 0x00);
    ret |= ov428_write_register(client, 0xc800, 0x04);
    ret |= ov428_write_register(client, 0xd000, 0x09);
    ret |= ov428_write_register(client, 0xd110, 0x14);
    ret |= ov428_write_register(client, 0xd111, 0x6b);
    ret |= ov428_write_register(client, 0xd410, 0x14);
    ret |= ov428_write_register(client, 0xd411, 0x6b);
    ret |= ov428_write_register(client, 0xd160, 0x01);
    ret |= ov428_write_register(client, 0xd161, 0x01);
    ret |= ov428_write_register(client, 0xd164, 0x01);
    ret |= ov428_write_register(client, 0xd165, 0x00);
    ret |= ov428_write_register(client, 0xd152, 0x03);
    ret |= ov428_write_register(client, 0xd154, 0x00);
    ret |= ov428_write_register(client, 0xd155, 0x00);
    ret |= ov428_write_register(client, 0xd156, 0x01);
    ret |= ov428_write_register(client, 0xd157, 0x01);
    ret |= ov428_write_register(client, 0xd158, 0x01);
    ret |= ov428_write_register(client, 0xd159, 0x01);
    ret |= ov428_write_register(client, 0xd15a, 0x01);
    ret |= ov428_write_register(client, 0xd15b, 0x01);
    ret |= ov428_write_register(client, 0xd166, 0x01);
    ret |= ov428_write_register(client, 0xd167, 0x00);
    ret |= ov428_write_register(client, 0xd0c0, 0x00);
    ret |= ov428_write_register(client, 0xd038, 0x40);
    ret |= ov428_write_register(client, 0xb016, 0x32);
    ret |= ov428_write_register(client, 0xb65d, 0x00);
    ret |= ov428_write_register(client, 0xc815, 0x40);
    ret |= ov428_write_register(client, 0xc816, 0x12);
    ret |= ov428_write_register(client, 0xc980, 0x00);
    ret |= ov428_write_register(client, 0xcc03, 0x0c);
    ret |= ov428_write_register(client, 0xcc04, 0x18);
    ret |= ov428_write_register(client, 0xcc05, 0x18);
    ret |= ov428_write_register(client, 0xcc26, 0x18);
    ret |= ov428_write_register(client, 0xc30c, 0xff);
    ret |= ov428_write_register(client, 0xcd00, 0x03);
    ret |= ov428_write_register(client, 0xcd01, 0xcc);
    ret |= ov428_write_register(client, 0xcd02, 0xbb);
    ret |= ov428_write_register(client, 0xcd03, 0x2a);
    ret |= ov428_write_register(client, 0xcd04, 0x2c);
    ret |= ov428_write_register(client, 0xcd05, 0x74);
    ret |= ov428_write_register(client, 0xc602, 0xf2);
    ret |= ov428_write_register(client, 0xc608, 0x68);
    ret |= ov428_write_register(client, 0xc680, 0x01);
    ret |= ov428_write_register(client, 0xc683, 0x12);
    ret |= ov428_write_register(client, 0xc68f, 0x06);
    ret |= ov428_write_register(client, 0xb773, 0x04);
    ret |= ov428_write_register(client, 0xb775, 0x11);
    ret |= ov428_write_register(client, 0xb776, 0x04);
    ret |= ov428_write_register(client, 0xb774, 0x0c);
    ret |= ov428_write_register(client, 0xb76d, 0xa1);
    ret |= ov428_write_register(client, 0xb906, 0x00);
    ret |= ov428_write_register(client, 0xb9d5, 0x00);
    ret |= ov428_write_register(client, 0xb907, 0x00);
    ret |= ov428_write_register(client, 0xb908, 0x00);
    ret |= ov428_write_register(client, 0xb909, 0x00);
    ret |= ov428_write_register(client, 0xb90c, 0x09);
    ret |= ov428_write_register(client, 0xb97a, 0x03);
    ret |= ov428_write_register(client, 0xb736, 0x30);
    ret |= ov428_write_register(client, 0xb90a, 0x00);
    ret |= ov428_write_register(client, 0xb911, 0x00);
    ret |= ov428_write_register(client, 0xb917, 0x01);
    ret |= ov428_write_register(client, 0xb918, 0x08);
    ret |= ov428_write_register(client, 0xb919, 0x02);
    ret |= ov428_write_register(client, 0xb920, 0x04);
    ret |= ov428_write_register(client, 0xb7c6, 0x34);
    ret |= ov428_write_register(client, 0xb7b0, 0x30);
    ret |= ov428_write_register(client, 0xb7b2, 0x01);
    ret |= ov428_write_register(client, 0xb914, 0x00);
    ret |= ov428_write_register(client, 0xb910, 0x40);
    ret |= ov428_write_register(client, 0xba9c, 0x0e);
    ret |= ov428_write_register(client, 0xba9d, 0x0c);
    ret |= ov428_write_register(client, 0xba9a, 0x2f);
    ret |= ov428_write_register(client, 0xb01c, 0xbc);
    ret |= ov428_write_register(client, 0xb01e, 0x1e);
    ret |= ov428_write_register(client, 0xb64b, 0x3a);
    ret |= ov428_write_register(client, 0xb640, 0x9e);
    ret |= ov428_write_register(client, 0xba49, 0x24);
    ret |= ov428_write_register(client, 0xba4a, 0x24);
    ret |= ov428_write_register(client, 0xba4b, 0x24);
    ret |= ov428_write_register(client, 0xba4c, 0x24);
    ret |= ov428_write_register(client, 0xba4d, 0x4a);
    ret |= ov428_write_register(client, 0xba4e, 0x4a);
    ret |= ov428_write_register(client, 0xba4f, 0x4a);
    ret |= ov428_write_register(client, 0xba50, 0x4a);
    ret |= ov428_write_register(client, 0xba52, 0x24);
    ret |= ov428_write_register(client, 0xba53, 0x24);
    ret |= ov428_write_register(client, 0xba54, 0x24);
    ret |= ov428_write_register(client, 0xba6c, 0x80);
    ret |= ov428_write_register(client, 0xba7b, 0x24);
    ret |= ov428_write_register(client, 0xba7c, 0x4a);
    ret |= ov428_write_register(client, 0xba7d, 0x4a);
    ret |= ov428_write_register(client, 0xba7e, 0x4a);
    ret |= ov428_write_register(client, 0xba7f, 0x4a);
    ret |= ov428_write_register(client, 0xbaa0, 0x44);
    ret |= ov428_write_register(client, 0xbaa6, 0x44);
    ret |= ov428_write_register(client, 0xbaaa, 0x0d);
    ret |= ov428_write_register(client, 0xbadc, 0x08);
    ret |= ov428_write_register(client, 0xb96d, 0xe0);
    ret |= ov428_write_register(client, 0xb96e, 0x11);
    ret |= ov428_write_register(client, 0xcc1f, 0x01);
    ret |= ov428_write_register(client, 0x8100, 0x01);
    ret |= ov428_write_register(client, 0xb218, 0x2c);
    ret |= ov428_write_register(client, 0xb821, 0x06);
    ret |= ov428_write_register(client, 0xb809, 0xe8);
    ret |= ov428_write_register(client, 0xb811, 0x01);
    ret |= ov428_write_register(client, 0xb501, 0x06);
    ret |= ov428_write_register(client, 0xb502, 0x44);
    ret |= ov428_write_register(client, 0xb508, 0x01);
    ret |= ov428_write_register(client, 0xb509, 0x00);
    ret |= ov428_write_register(client, 0xb541, 0x00);
    ret |= ov428_write_register(client, 0xb542, 0x04);
    ret |= ov428_write_register(client, 0xb548, 0x01);
    ret |= ov428_write_register(client, 0xb549, 0x00);
    ret |= ov428_write_register(client, 0xb504, 0x48);
    ret |= ov428_write_register(client, 0xb65e, 0x01);
    ret |= ov428_write_register(client, 0xd000, 0x09);
    ret |= ov428_write_register(client, 0x8000, 0x00);
    ret |= ov428_write_register(client, 0x4b00, 0x10);
    ret |= ov428_write_register(client, 0x4b00, 0x20);
    ret |= ov428_write_register(client, 0x0100, 0x01);


    return ret;
}


// Implement control handler (simplified example)
static int ov428_initialize_controls(struct v4l2_subdev *sd) {
    struct v4l2_ctrl_handler *handler;
    handler = &sd->ctrl_handler;
    v4l2_ctrl_handler_init(handler, 1);
    
    v4l2_ctrl_new_std(handler, &v4l2_ctrl_ops_dummy, V4L2_CID_BRIGHTNESS, 0, 255, 1, 128);
    
    if (handler->error) {
        pr_err("Failed to add controls\n");
        return handler->error;
    }
    return 0;
}

static const struct v4l2_subdev_video_ops ov428_video_ops = {
    .s_stream = ov428_s_stream, // Unchanged
};

static const struct v4l2_subdev_ops ov428_subdev_ops = {
    .video = &ov428_video_ops,
};

static int ov428_probe(struct i2c_client *client, const struct i2c_device_id *id) {
    struct v4l2_subdev *sd;
    struct device *dev = &client->dev;
    int ret;

    sd = devm_kzalloc(dev, sizeof(*sd), GFP_KERNEL);
    if (!sd)
        return -ENOMEM;

    v4l2_i2c_subdev_init(sd, client, &ov428_subdev_ops);
    sd->flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;
    
    // Initialize control handlers here
    ret = ov428_initialize_controls(sd);
    if (ret)
        return ret;

    sd->owner = THIS_MODULE;
    sd->dev = dev;
    
    // Initialize media entity
    sd->entity.function = MEDIA_ENT_F_CAM_SENSOR;
    ret = media_entity_pads_init(&sd->entity, 0, NULL);
    if (ret < 0)
        return ret;

    // Perform sensor-specific initialization
    ret = ov428_set_mode(client);
    if (ret < 0) {
        media_entity_cleanup(&sd->entity);
        return ret;
    }

    return 0;
}

static int ov428_remove(struct i2c_client *client) {
    struct v4l2_subdev *sd = i2c_get_clientdata(client);

    media_entity_cleanup(&sd->entity);
    v4l2_ctrl_handler_free(sd->ctrl_handler);
    
    return 0;
}

static const struct i2c_device_id ov428_id[] = {
    { "ov428", 0 },
    { }
};
MODULE_DEVICE_TABLE(i2c, ov428_id);

static struct i2c_driver ov428_driver = {
    .driver = {
        .name = "ov428",
        .owner = THIS_MODULE,
    },
    .probe = ov428_probe,
    .remove = ov428_remove,
    .id_table = ov428_id,
};

module_i2c_driver(ov428_driver);

MODULE_DESCRIPTION("OV428 Camera Driver");
MODULE_LICENSE("GPL");
