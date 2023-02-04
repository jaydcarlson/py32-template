# Puya PY32 MCU SDK
This repo contains a GCC/Makefile-based build system for Puya PY32 MCUs, including the PY32F002A, PY32F003, and PY32F030. 

Also included are vscode build/launch configs using Cortex-Debug and pyOCD.

## pyOCD support
Puya's DFP is not currently indexed anywhere, so pyOCD can't automatically download it with the typical `pack update` and `pack install` commands. However, we can manually download and extract this pack, and then install the pack using cmsis-pack-manager (which PyOCD uses under the hood)

First, get a copy of the DFP, which is found in Puya's PY32 SDK download available on their [PY32 web page](https://www.puyasemi.com/cpzx3/info_271_aid_247_kid_246.html). The download link is listed under the "Datasheet" column in the far right of the device table — you can [directly download the file here](https://www.puyasemi.com/uploadfiles/2022/11/PY-MCU%E8%B5%84%E6%96%99-20221117.rar), though this link may be out of date. If you extract this RAR, you'll end up with documentation, code samples, and the Puya.PY32F0xx_DFP.1.1.0.pack DFP pack.

Next, unzip `Puya.PY32F0xx_DFP.1.1.0.pack` (it's just a ZIP with a .pack extension). Then, copy the `pdesc` file to cmsis-pack-manager's repository along with all the other pdsc files (this will be located in your Python distribution). It needs to be renamed to `Puya.PY32F0xx_DFP.1.1.0.pdsc` (with the version numbers present).

Next, copy the original DFP pack file to `Puya\PY32F0xx_DFP\1.1.0.pack` creating directories and renaming the pack file accordingly. 

Now, add the pack to cmsis-pack-manager:
```
PS C:\> pack-manager add-packs Puya.PY32F0xx_DFP.1.1.0.pdsc
```
Now you can install the actual target support in PyOCD:
```
PS C:\> pyocd pack find PY32
  Part          Vendor   Pack                Version   Installed
------------------------------------------------------------------
  PY32F002Ax5   Puya     Puya.PY32F0xx_DFP   1.1.0     True
  PY32F003x4    Puya     Puya.PY32F0xx_DFP   1.1.0     True
  PY32F003x6    Puya     Puya.PY32F0xx_DFP   1.1.0     True
  PY32F003x8    Puya     Puya.PY32F0xx_DFP   1.1.0     True
  PY32F030x3    Puya     Puya.PY32F0xx_DFP   1.1.0     True
  PY32F030x4    Puya     Puya.PY32F0xx_DFP   1.1.0     True
  PY32F030x6    Puya     Puya.PY32F0xx_DFP   1.1.0     True
  PY32F030x7    Puya     Puya.PY32F0xx_DFP   1.1.0     True
  PY32F030x8    Puya     Puya.PY32F0xx_DFP   1.1.0     True
  PY32F072xB    Puya     Puya.PY32F0xx_DFP   1.1.0     True

PS C:\> pyocd pack install PY32F003x8
```

## J-Link Support
Using the [J-Link Device Support Kit Segger Wiki page](https://wiki.segger.com/J-Link_Device_Support_Kit) as a reference, create a `JLinkDevices\Puya\PY32` directory structure in your home directory's Segger application data folder (on Windows, it's in `C:\Users\<USER>\AppData\Roaming\SEGGER\`). Pull in all the FLM files from the aforementioned DFP to this directory, and add a Devices.XML file that points J-Link to these files. Here's an example for the PY32F002Ax5:
```
<Database>
  <Device>
    <ChipInfo Vendor="Puya" Name="PY32F002Ax5" WorkRAMAddr="0x20000000" WorkRAMSize="3072" Core="JLINK_CORE_CORTEX_M0" />
    <FlashBankInfo Name="Internal code flash" BaseAddr="0x08000000" AlwaysPresent="1" >
      <LoaderInfo Name="Default" MaxSize="0x5000" Loader="PY32F0xx_20.FLM" LoaderType="FLASH_ALGO_TYPE_OPEN" />
    </FlashBankInfo>
  </Device>
</Database>
``` 