/**************************************************************************/
/*!
    @file     Adafruit_PN532.h
    @author   Adafruit Industries
	@license  BSD (see license.txt)


	This is a library for the Adafruit PN532 NFC/RFID breakout boards
	This library works with the Adafruit NFC breakout
	----> https://www.adafruit.com/products/364

	Check out the links above for our tutorials and wiring diagrams
	These chips use SPI to communicate, 4 required to interface

	Adafruit invests time and resources providing this open source code,
	please support Adafruit and open-source hardware by purchasing
	products from Adafruit!

	@section  HISTORY

	v1.1  - Added full command list
          - Added 'verbose' mode flag to constructor to toggle debug output
          - Changed readPassiveTargetID() to return variable length values

*/
/**************************************************************************/

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#define PN532_PREAMBLE                      (0x00)
#define PN532_STARTCODE1                    (0x00)
#define PN532_STARTCODE2                    (0xFF)
#define PN532_POSTAMBLE                     (0x00)

#define PN532_HOSTTOPN532                   (0xD4)

// PN532 Commands
#define PN532_COMMAND_DIAGNOSE              (0x00)
#define PN532_COMMAND_GETFIRMWAREVERSION    (0x02)
#define PN532_COMMAND_GETGENERALSTATUS      (0x04)
#define PN532_COMMAND_READREGISTER          (0x06)
#define PN532_COMMAND_WRITEREGISTER         (0x08)
#define PN532_COMMAND_READGPIO              (0x0C)
#define PN532_COMMAND_WRITEGPIO             (0x0E)
#define PN532_COMMAND_SETSERIALBAUDRATE     (0x10)
#define PN532_COMMAND_SETPARAMETERS         (0x12)
#define PN532_COMMAND_SAMCONFIGURATION      (0x14)
#define PN532_COMMAND_POWERDOWN             (0x16)
#define PN532_COMMAND_RFCONFIGURATION       (0x32)
#define PN532_COMMAND_RFREGULATIONTEST      (0x58)
#define PN532_COMMAND_INJUMPFORDEP          (0x56)
#define PN532_COMMAND_INJUMPFORPSL          (0x46)
#define PN532_COMMAND_INLISTPASSIVETARGET   (0x4A)
#define PN532_COMMAND_INATR                 (0x50)
#define PN532_COMMAND_INPSL                 (0x4E)
#define PN532_COMMAND_INDATAEXCHANGE        (0x40)
#define PN532_COMMAND_INCOMMUNICATETHRU     (0x42)
#define PN532_COMMAND_INDESELECT            (0x44)
#define PN532_COMMAND_INRELEASE             (0x52)
#define PN532_COMMAND_INSELECT              (0x54)
#define PN532_COMMAND_INAUTOPOLL            (0x60)
#define PN532_COMMAND_TGINITASTARGET        (0x8C)
#define PN532_COMMAND_TGSETGENERALBYTES     (0x92)
#define PN532_COMMAND_TGGETDATA             (0x86)
#define PN532_COMMAND_TGSETDATA             (0x8E)
#define PN532_COMMAND_TGSETMETADATA         (0x94)
#define PN532_COMMAND_TGGETINITIATORCOMMAND (0x88)
#define PN532_COMMAND_TGRESPONSETOINITIATOR (0x90)
#define PN532_COMMAND_TGGETTARGETSTATUS     (0x8A)

#define PN532_WAKEUP                        (0x55)

#define PN532_SPI_STATREAD                  (0x02)
#define PN532_SPI_DATAWRITE                 (0x01)
#define PN532_SPI_DATAREAD                  (0x03)
#define PN532_SPI_READY                     (0x01)

#define PN532_MIFARE_ISO14443A              (0x00)

// Mifare Commands
#define MIFARE_CMD_AUTH_A                   (0x60)
#define MIFARE_CMD_AUTH_B                   (0x61)
#define MIFARE_CMD_READ                     (0x30)
#define MIFARE_CMD_WRITE                    (0xA0)
#define MIFARE_CMD_TRANSFER                 (0xB0)
#define MIFARE_CMD_DECREMENT                (0xC0)
#define MIFARE_CMD_INCREMENT                (0xC1)
#define MIFARE_CMD_STORE                    (0xC2)

// Prefixes for NDEF Records (to identify record type)
#define NDEF_URIPREFIX_NONE                 (0x00)
#define NDEF_URIPREFIX_HTTP_WWWDOT          (0x01)
#define NDEF_URIPREFIX_HTTPS_WWWDOT         (0x02)
#define NDEF_URIPREFIX_HTTP                 (0x03)
#define NDEF_URIPREFIX_HTTPS                (0x04)
#define NDEF_URIPREFIX_TEL                  (0x05)
#define NDEF_URIPREFIX_MAILTO               (0x06)
#define NDEF_URIPREFIX_FTP_ANONAT           (0x07)
#define NDEF_URIPREFIX_FTP_FTPDOT           (0x08)
#define NDEF_URIPREFIX_FTPS                 (0x09)
#define NDEF_URIPREFIX_SFTP                 (0x0A)
#define NDEF_URIPREFIX_SMB                  (0x0B)
#define NDEF_URIPREFIX_NFS                  (0x0C)
#define NDEF_URIPREFIX_FTP                  (0x0D)
#define NDEF_URIPREFIX_DAV                  (0x0E)
#define NDEF_URIPREFIX_NEWS                 (0x0F)
#define NDEF_URIPREFIX_TELNET               (0x10)
#define NDEF_URIPREFIX_IMAP                 (0x11)
#define NDEF_URIPREFIX_RTSP                 (0x12)
#define NDEF_URIPREFIX_URN                  (0x13)
#define NDEF_URIPREFIX_POP                  (0x14)
#define NDEF_URIPREFIX_SIP                  (0x15)
#define NDEF_URIPREFIX_SIPS                 (0x16)
#define NDEF_URIPREFIX_TFTP                 (0x17)
#define NDEF_URIPREFIX_BTSPP                (0x18)
#define NDEF_URIPREFIX_BTL2CAP              (0x19)
#define NDEF_URIPREFIX_BTGOEP               (0x1A)
#define NDEF_URIPREFIX_TCPOBEX              (0x1B)
#define NDEF_URIPREFIX_IRDAOBEX             (0x1C)
#define NDEF_URIPREFIX_FILE                 (0x1D)
#define NDEF_URIPREFIX_URN_EPC_ID           (0x1E)
#define NDEF_URIPREFIX_URN_EPC_TAG          (0x1F)
#define NDEF_URIPREFIX_URN_EPC_PAT          (0x20)
#define NDEF_URIPREFIX_URN_EPC_RAW          (0x21)
#define NDEF_URIPREFIX_URN_EPC              (0x22)
#define NDEF_URIPREFIX_URN_NFC              (0x23)

#define PN532_GPIO_VALIDATIONBIT            (0x80)
#define PN532_GPIO_P30                      (0)
#define PN532_GPIO_P31                      (1)
#define PN532_GPIO_P32                      (2)
#define PN532_GPIO_P33                      (3)
#define PN532_GPIO_P34                      (4)
#define PN532_GPIO_P35                      (5)


#define MIFARE_DESFIRE_MAX_AIDS             (26)
#define MIFARE_DESFIRE_MAX_FILEIDS          (16)


#define MIFARE_DESFIRE_STANDARD_FILE        (0)
#define MIFARE_DESFIRE_BACKUP_FILE          (1)
#define MIFARE_DESFIRE_VALUE_FILE           (2)
#define MIFARE_DESFIRE_LINEAR_RECORD_FILE   (3)
#define MIFARE_DESFIRE_CYCLIC_RECORD_FILE   (4)


struct DESFireVersion {
  uint8_t   HwVendorId;
  uint8_t   SwVendorId;

  /* msb byte major, lsb byte minor */
  uint16_t  HwVersion;
  uint16_t  SwVersion;

  /* storage size is 2 << StorgeExponent */
  uint8_t   HwStorageExponent;
  uint8_t   SwStorageExponent;

  /* SerialNumber is the card UID, batch number the production batch number */
  uint8_t   SerialNumber[7];
  uint8_t   BatchNumber[5];

  uint8_t   CalendarWeek;
  uint8_t   Year;
};


struct DESFireFileSetting {
  uint8_t   Type;
  uint8_t   CommunicationSettings;
  uint16_t  AccessRights;

  union {
    /* Standard files only have a size which is 24 bit wide */
    struct {
      uint32_t  FileSize;
    };

    /* Values have limits and special credit properties. */
    struct {
      uint32_t  LowerLimit;
      uint32_t  UpperLimit;
      uint32_t  LimitedCreditValue;
      uint8_t   LimitedCreditEnabled;
    };

    /* Records */
    struct {
      uint32_t  RecordSize;
      uint32_t  MaxRecords;
      uint32_t  CurrentRecords;
    };
  } Settings;
};




class Adafruit_PN532{
 public:
  Adafruit_PN532(uint8_t cs, uint8_t clk, uint8_t mosi, uint8_t miso);
  void begin(void);

  // Generic PN532 functions
  boolean SAMConfig(void);
  uint32_t getFirmwareVersion(void);
  boolean sendCommandCheckAck(uint8_t *cmd, uint8_t cmdlen, uint16_t timeout = 1000);
  boolean writeGPIO(uint8_t pinstate);
  uint8_t readGPIO(void);

  // ISO14443A functions
  boolean readPassiveTargetID(uint8_t cardbaudrate, uint8_t * uid, uint8_t * uidLength);

  // Mifare Classic functions
  bool mifareclassic_IsFirstBlock (uint32_t uiBlock);
  bool mifareclassic_IsTrailerBlock (uint32_t uiBlock);
  uint8_t mifareclassic_AuthenticateBlock (uint8_t * uid, uint8_t uidLen, uint32_t blockNumber, uint8_t keyNumber, uint8_t * keyData);
  uint8_t mifareclassic_ReadDataBlock (uint8_t blockNumber, uint8_t * data);
  uint8_t mifareclassic_WriteDataBlock (uint8_t blockNumber, uint8_t * data);
  uint8_t mifareclassic_FormatNDEF (void);
  uint8_t mifareclassic_WriteNDEFURI (uint8_t sectorNumber, uint8_t uriIdentifier, const char * url);

  // Mifare DESFire functions
  uint8_t desfire_GetVersion(DESFireVersion* v);
  uint8_t desfire_GetApplicationIDs(uint8_t* ids, uint8_t* len);
  uint8_t desfire_GetFileIDs(uint8_t* ids, uint8_t* len);
  uint8_t desfire_SelectApplication(uint8_t* aid);
  uint8_t desfire_GetFileSettings(uint8_t fid, DESFireFileSetting* s);
  uint8_t desfire_ReadData(uint8_t fid, uint32_t offset, uint32_t length, uint8_t* dest, uint16_t destLen);
  uint8_t desfire_GetKeyVersion(uint8_t* keySettings, uint8_t* noOfKeys);


  // Mifare Ultralight functions
  uint8_t mifareultralight_ReadPage (uint8_t page, uint8_t * buffer);

  // Help functions to display formatted text
  static void PrintHex(const byte * data, const uint32_t numBytes);
  static void PrintHexChar(const byte * pbtData, const uint32_t numBytes);

 protected:
  uint8_t desfire_readDataHelper(uint8_t* dest, uint16_t destLen, uint16_t* readBytes);
  uint8_t desfire_sendAndRead(uint8_t cmdLen, uint8_t dataLen);
  uint8_t desfire_getError();

 private:
  uint8_t _ss, _clk, _mosi, _miso;
  uint8_t _uid[7];  // ISO14443A uid
  uint8_t _uidLen;  // uid len
  uint8_t _key[6];  // Mifare Classic key

  boolean spi_readack();
  uint8_t readspistatus(void);
  void readspidata(uint8_t* buff, uint8_t n);
  void spiwritecommand(uint8_t* cmd, uint8_t cmdlen);
  void spiwrite(uint8_t c);
  uint8_t spiread(void);
};
