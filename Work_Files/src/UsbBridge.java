package org.qtproject.qt5.android.bindings;

import android.*;
import android.hardware.usb.*;
import android.hardware.usb.UsbManager;

public class UsbBridge
{
    public int fd = 0;
    public UsbBridge(int fdt)
    {
        fd = fdt;
    }

    public int giveFD()
    {
        return fd;
    }


}
