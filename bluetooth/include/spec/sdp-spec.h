/*
  Copyright 2013-2014 bcstack.org

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#ifndef _SDP_SPEC_H_
#define _SDP_SPEC_H_

// Data Element Types
enum {
    SDP_DE_NIL = 0,
    SDP_DE_UINT,
    SDP_DE_INT,
    SDP_DE_UUID,
    SDP_DE_STRING,
    SDP_DE_BOOL,
    SDP_DE_DES,
    SDP_DE_DEA,
    SDP_DE_URL
};

// Data Element Size
enum {
    SDP_DE_SIZE_8 = 0,
    SDP_DE_SIZE_16,
    SDP_DE_SIZE_32,
    SDP_DE_SIZE_64,
    SDP_DE_SIZE_128,
    SDP_DE_SIZE_VAR_8,
    SDP_DE_SIZE_VAR_16,
    SDP_DE_SIZE_VAR_32
};

// SDP PDU ID
enum {
    SDP_ERROR_RESPONSE = 1,
    SDP_SERVICE_SEARCH_REQUEST,
    SDP_SERVICE_SEARCH_RESPONSE,
    SDP_SERVICE_ATTRIBUTE_REQUEST,
    SDP_SERVICE_ATTRIBUTE_RESPONSE,
    SDP_SERVICE_SEARCH_ATTRIBUTE_REQUEST,
    SDP_SERVICE_SEARCH_ATTRIBUTE_RESPONSE,
};

// UNIVERSAL ATTRIBUTE DEFINITIONS
#define SDP_ServiceRecordHandle     0x0000
#define SDP_ServiceClassIDList      0x0001
#define SDP_ServiceRecordState      0x0002
#define SDP_ServiceID               0x0003
#define SDP_ProtocolDescriptorList  0x0004
#define SDP_BrowseGroupList                 0x0005
#define SDP_LanguageBaseAttributeIDList 0x0006
#define SDP_ServiceInfoTimeToLive       0x0007
#define SDP_ServiceAvailability         0x0008
#define SDP_BluetoothProfileDescriptorList 0x0009
#define SDP_DocumentationURL            0x000a
#define SDP_ClientExecutableURL     0x000b
#define SDP_IconURL                 0x000c
#define SDP_AdditionalProtocolDescriptorList 0x000d
#define SDP_SupportedFormatsList    0x0303

// SERVICE CLASSES
#define SDP_OBEXObjectPush    0x1105
#define SDP_OBEXFileTransfer  0x1106
#define SDP_PublicBrowseGroup 0x1002

// PROTOCOLS
#define SDP_SDPProtocol       0x0001
#define SDP_UDPProtocol       0x0002
#define SDP_RFCOMMProtocol    0x0003
#define SDP_OBEXProtocol      0x0008
#define SDP_L2CAPProtocol     0x0100

// OFFSETS FOR LOCALIZED ATTRIBUTES - SDP_LanguageBaseAttributeIDList
#define SDP_Offest_ServiceName      0x0000
#define SDP_Offest_ServiceDescription 0x0001
#define SDP_Offest_ProviderName     0x0002

#endif // _SDP_SPEC_H_
