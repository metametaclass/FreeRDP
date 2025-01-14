
#include <stdio.h>
#include <winpr/crt.h>
#include <winpr/windows.h>
#include <winpr/path.h>
#include <winpr/crypto.h>

#include <freerdp/client/file.h>

static const BYTE testRdpFileUTF16[] =
{
	0xff, 0xfe, 0x73, 0x00, 0x63, 0x00, 0x72, 0x00, 0x65, 0x00, 0x65, 0x00,
	0x6e, 0x00, 0x20, 0x00, 0x6d, 0x00, 0x6f, 0x00, 0x64, 0x00, 0x65, 0x00,
	0x20, 0x00, 0x69, 0x00, 0x64, 0x00, 0x3a, 0x00, 0x69, 0x00, 0x3a, 0x00,
	0x32, 0x00, 0x0d, 0x00, 0x0a, 0x00, 0x75, 0x00, 0x73, 0x00, 0x65, 0x00,
	0x20, 0x00, 0x6d, 0x00, 0x75, 0x00, 0x6c, 0x00, 0x74, 0x00, 0x69, 0x00,
	0x6d, 0x00, 0x6f, 0x00, 0x6e, 0x00, 0x3a, 0x00, 0x69, 0x00, 0x3a, 0x00,
	0x30, 0x00, 0x0d, 0x00, 0x0a, 0x00, 0x64, 0x00, 0x65, 0x00, 0x73, 0x00,
	0x6b, 0x00, 0x74, 0x00, 0x6f, 0x00, 0x70, 0x00, 0x77, 0x00, 0x69, 0x00,
	0x64, 0x00, 0x74, 0x00, 0x68, 0x00, 0x3a, 0x00, 0x69, 0x00, 0x3a, 0x00,
	0x31, 0x00, 0x39, 0x00, 0x32, 0x00, 0x30, 0x00, 0x0d, 0x00, 0x0a, 0x00,
	0x64, 0x00, 0x65, 0x00, 0x73, 0x00, 0x6b, 0x00, 0x74, 0x00, 0x6f, 0x00,
	0x70, 0x00, 0x68, 0x00, 0x65, 0x00, 0x69, 0x00, 0x67, 0x00, 0x68, 0x00,
	0x74, 0x00, 0x3a, 0x00, 0x69, 0x00, 0x3a, 0x00, 0x31, 0x00, 0x30, 0x00,
	0x38, 0x00, 0x30, 0x00, 0x0d, 0x00, 0x0a, 0x00, 0x73, 0x00, 0x65, 0x00,
	0x73, 0x00, 0x73, 0x00, 0x69, 0x00, 0x6f, 0x00, 0x6e, 0x00, 0x20, 0x00,
	0x62, 0x00, 0x70, 0x00, 0x70, 0x00, 0x3a, 0x00, 0x69, 0x00, 0x3a, 0x00,
	0x33, 0x00, 0x32, 0x00, 0x0d, 0x00, 0x0a, 0x00, 0x77, 0x00, 0x69, 0x00,
	0x6e, 0x00, 0x70, 0x00, 0x6f, 0x00, 0x73, 0x00, 0x73, 0x00, 0x74, 0x00,
	0x72, 0x00, 0x3a, 0x00, 0x73, 0x00, 0x3a, 0x00, 0x30, 0x00, 0x2c, 0x00,
	0x31, 0x00, 0x2c, 0x00, 0x35, 0x00, 0x35, 0x00, 0x33, 0x00, 0x2c, 0x00,
	0x32, 0x00, 0x31, 0x00, 0x31, 0x00, 0x2c, 0x00, 0x31, 0x00, 0x33, 0x00,
	0x35, 0x00, 0x33, 0x00, 0x2c, 0x00, 0x38, 0x00, 0x31, 0x00, 0x31, 0x00,
	0x0d, 0x00, 0x0a, 0x00, 0x63, 0x00, 0x6f, 0x00, 0x6d, 0x00, 0x70, 0x00,
	0x72, 0x00, 0x65, 0x00, 0x73, 0x00, 0x73, 0x00, 0x69, 0x00, 0x6f, 0x00,
	0x6e, 0x00, 0x3a, 0x00, 0x69, 0x00, 0x3a, 0x00, 0x31, 0x00, 0x0d, 0x00,
	0x0a, 0x00, 0x6b, 0x00, 0x65, 0x00, 0x79, 0x00, 0x62, 0x00, 0x6f, 0x00,
	0x61, 0x00, 0x72, 0x00, 0x64, 0x00, 0x68, 0x00, 0x6f, 0x00, 0x6f, 0x00,
	0x6b, 0x00, 0x3a, 0x00, 0x69, 0x00, 0x3a, 0x00, 0x32, 0x00, 0x0d, 0x00,
	0x0a, 0x00, 0x61, 0x00, 0x75, 0x00, 0x64, 0x00, 0x69, 0x00, 0x6f, 0x00,
	0x63, 0x00, 0x61, 0x00, 0x70, 0x00, 0x74, 0x00, 0x75, 0x00, 0x72, 0x00,
	0x65, 0x00, 0x6d, 0x00, 0x6f, 0x00, 0x64, 0x00, 0x65, 0x00, 0x3a, 0x00,
	0x69, 0x00, 0x3a, 0x00, 0x30, 0x00, 0x0d, 0x00, 0x0a, 0x00, 0x76, 0x00,
	0x69, 0x00, 0x64, 0x00, 0x65, 0x00, 0x6f, 0x00, 0x70, 0x00, 0x6c, 0x00,
	0x61, 0x00, 0x79, 0x00, 0x62, 0x00, 0x61, 0x00, 0x63, 0x00, 0x6b, 0x00,
	0x6d, 0x00, 0x6f, 0x00, 0x64, 0x00, 0x65, 0x00, 0x3a, 0x00, 0x69, 0x00,
	0x3a, 0x00, 0x31, 0x00, 0x0d, 0x00, 0x0a, 0x00, 0x63, 0x00, 0x6f, 0x00,
	0x6e, 0x00, 0x6e, 0x00, 0x65, 0x00, 0x63, 0x00, 0x74, 0x00, 0x69, 0x00,
	0x6f, 0x00, 0x6e, 0x00, 0x20, 0x00, 0x74, 0x00, 0x79, 0x00, 0x70, 0x00,
	0x65, 0x00, 0x3a, 0x00, 0x69, 0x00, 0x3a, 0x00, 0x37, 0x00, 0x0d, 0x00,
	0x0a, 0x00, 0x6e, 0x00, 0x65, 0x00, 0x74, 0x00, 0x77, 0x00, 0x6f, 0x00,
	0x72, 0x00, 0x6b, 0x00, 0x61, 0x00, 0x75, 0x00, 0x74, 0x00, 0x6f, 0x00,
	0x64, 0x00, 0x65, 0x00, 0x74, 0x00, 0x65, 0x00, 0x63, 0x00, 0x74, 0x00,
	0x3a, 0x00, 0x69, 0x00, 0x3a, 0x00, 0x31, 0x00, 0x0d, 0x00, 0x0a, 0x00,
	0x62, 0x00, 0x61, 0x00, 0x6e, 0x00, 0x64, 0x00, 0x77, 0x00, 0x69, 0x00,
	0x64, 0x00, 0x74, 0x00, 0x68, 0x00, 0x61, 0x00, 0x75, 0x00, 0x74, 0x00,
	0x6f, 0x00, 0x64, 0x00, 0x65, 0x00, 0x74, 0x00, 0x65, 0x00, 0x63, 0x00,
	0x74, 0x00, 0x3a, 0x00, 0x69, 0x00, 0x3a, 0x00, 0x31, 0x00, 0x0d, 0x00,
	0x0a, 0x00, 0x64, 0x00, 0x69, 0x00, 0x73, 0x00, 0x70, 0x00, 0x6c, 0x00,
	0x61, 0x00, 0x79, 0x00, 0x63, 0x00, 0x6f, 0x00, 0x6e, 0x00, 0x6e, 0x00,
	0x65, 0x00, 0x63, 0x00, 0x74, 0x00, 0x69, 0x00, 0x6f, 0x00, 0x6e, 0x00,
	0x62, 0x00, 0x61, 0x00, 0x72, 0x00, 0x3a, 0x00, 0x69, 0x00, 0x3a, 0x00,
	0x31, 0x00, 0x0d, 0x00, 0x0a, 0x00, 0x65, 0x00, 0x6e, 0x00, 0x61, 0x00,
	0x62, 0x00, 0x6c, 0x00, 0x65, 0x00, 0x77, 0x00, 0x6f, 0x00, 0x72, 0x00,
	0x6b, 0x00, 0x73, 0x00, 0x70, 0x00, 0x61, 0x00, 0x63, 0x00, 0x65, 0x00,
	0x72, 0x00, 0x65, 0x00, 0x63, 0x00, 0x6f, 0x00, 0x6e, 0x00, 0x6e, 0x00,
	0x65, 0x00, 0x63, 0x00, 0x74, 0x00, 0x3a, 0x00, 0x69, 0x00, 0x3a, 0x00,
	0x30, 0x00, 0x0d, 0x00, 0x0a, 0x00, 0x64, 0x00, 0x69, 0x00, 0x73, 0x00,
	0x61, 0x00, 0x62, 0x00, 0x6c, 0x00, 0x65, 0x00, 0x20, 0x00, 0x77, 0x00,
	0x61, 0x00, 0x6c, 0x00, 0x6c, 0x00, 0x70, 0x00, 0x61, 0x00, 0x70, 0x00,
	0x65, 0x00, 0x72, 0x00, 0x3a, 0x00, 0x69, 0x00, 0x3a, 0x00, 0x30, 0x00,
	0x0d, 0x00, 0x0a, 0x00, 0x61, 0x00, 0x6c, 0x00, 0x6c, 0x00, 0x6f, 0x00,
	0x77, 0x00, 0x20, 0x00, 0x66, 0x00, 0x6f, 0x00, 0x6e, 0x00, 0x74, 0x00,
	0x20, 0x00, 0x73, 0x00, 0x6d, 0x00, 0x6f, 0x00, 0x6f, 0x00, 0x74, 0x00,
	0x68, 0x00, 0x69, 0x00, 0x6e, 0x00, 0x67, 0x00, 0x3a, 0x00, 0x69, 0x00,
	0x3a, 0x00, 0x30, 0x00, 0x0d, 0x00, 0x0a, 0x00, 0x61, 0x00, 0x6c, 0x00,
	0x6c, 0x00, 0x6f, 0x00, 0x77, 0x00, 0x20, 0x00, 0x64, 0x00, 0x65, 0x00,
	0x73, 0x00, 0x6b, 0x00, 0x74, 0x00, 0x6f, 0x00, 0x70, 0x00, 0x20, 0x00,
	0x63, 0x00, 0x6f, 0x00, 0x6d, 0x00, 0x70, 0x00, 0x6f, 0x00, 0x73, 0x00,
	0x69, 0x00, 0x74, 0x00, 0x69, 0x00, 0x6f, 0x00, 0x6e, 0x00, 0x3a, 0x00,
	0x69, 0x00, 0x3a, 0x00, 0x30, 0x00, 0x0d, 0x00, 0x0a, 0x00, 0x64, 0x00,
	0x69, 0x00, 0x73, 0x00, 0x61, 0x00, 0x62, 0x00, 0x6c, 0x00, 0x65, 0x00,
	0x20, 0x00, 0x66, 0x00, 0x75, 0x00, 0x6c, 0x00, 0x6c, 0x00, 0x20, 0x00,
	0x77, 0x00, 0x69, 0x00, 0x6e, 0x00, 0x64, 0x00, 0x6f, 0x00, 0x77, 0x00,
	0x20, 0x00, 0x64, 0x00, 0x72, 0x00, 0x61, 0x00, 0x67, 0x00, 0x3a, 0x00,
	0x69, 0x00, 0x3a, 0x00, 0x31, 0x00, 0x0d, 0x00, 0x0a, 0x00, 0x64, 0x00,
	0x69, 0x00, 0x73, 0x00, 0x61, 0x00, 0x62, 0x00, 0x6c, 0x00, 0x65, 0x00,
	0x20, 0x00, 0x6d, 0x00, 0x65, 0x00, 0x6e, 0x00, 0x75, 0x00, 0x20, 0x00,
	0x61, 0x00, 0x6e, 0x00, 0x69, 0x00, 0x6d, 0x00, 0x73, 0x00, 0x3a, 0x00,
	0x69, 0x00, 0x3a, 0x00, 0x31, 0x00, 0x0d, 0x00, 0x0a, 0x00, 0x64, 0x00,
	0x69, 0x00, 0x73, 0x00, 0x61, 0x00, 0x62, 0x00, 0x6c, 0x00, 0x65, 0x00,
	0x20, 0x00, 0x74, 0x00, 0x68, 0x00, 0x65, 0x00, 0x6d, 0x00, 0x65, 0x00,
	0x73, 0x00, 0x3a, 0x00, 0x69, 0x00, 0x3a, 0x00, 0x30, 0x00, 0x0d, 0x00,
	0x0a, 0x00, 0x64, 0x00, 0x69, 0x00, 0x73, 0x00, 0x61, 0x00, 0x62, 0x00,
	0x6c, 0x00, 0x65, 0x00, 0x20, 0x00, 0x63, 0x00, 0x75, 0x00, 0x72, 0x00,
	0x73, 0x00, 0x6f, 0x00, 0x72, 0x00, 0x20, 0x00, 0x73, 0x00, 0x65, 0x00,
	0x74, 0x00, 0x74, 0x00, 0x69, 0x00, 0x6e, 0x00, 0x67, 0x00, 0x3a, 0x00,
	0x69, 0x00, 0x3a, 0x00, 0x30, 0x00, 0x0d, 0x00, 0x0a, 0x00, 0x62, 0x00,
	0x69, 0x00, 0x74, 0x00, 0x6d, 0x00, 0x61, 0x00, 0x70, 0x00, 0x63, 0x00,
	0x61, 0x00, 0x63, 0x00, 0x68, 0x00, 0x65, 0x00, 0x70, 0x00, 0x65, 0x00,
	0x72, 0x00, 0x73, 0x00, 0x69, 0x00, 0x73, 0x00, 0x74, 0x00, 0x65, 0x00,
	0x6e, 0x00, 0x61, 0x00, 0x62, 0x00, 0x6c, 0x00, 0x65, 0x00, 0x3a, 0x00,
	0x69, 0x00, 0x3a, 0x00, 0x31, 0x00, 0x0d, 0x00, 0x0a, 0x00, 0x66, 0x00,
	0x75, 0x00, 0x6c, 0x00, 0x6c, 0x00, 0x20, 0x00, 0x61, 0x00, 0x64, 0x00,
	0x64, 0x00, 0x72, 0x00, 0x65, 0x00, 0x73, 0x00, 0x73, 0x00, 0x3a, 0x00,
	0x73, 0x00, 0x3a, 0x00, 0x4c, 0x00, 0x41, 0x00, 0x42, 0x00, 0x31, 0x00,
	0x2d, 0x00, 0x57, 0x00, 0x37, 0x00, 0x2d, 0x00, 0x44, 0x00, 0x4d, 0x00,
	0x2d, 0x00, 0x30, 0x00, 0x31, 0x00, 0x2e, 0x00, 0x6c, 0x00, 0x61, 0x00,
	0x62, 0x00, 0x31, 0x00, 0x2e, 0x00, 0x61, 0x00, 0x77, 0x00, 0x61, 0x00,
	0x6b, 0x00, 0x65, 0x00, 0x2e, 0x00, 0x6c, 0x00, 0x6f, 0x00, 0x63, 0x00,
	0x61, 0x00, 0x6c, 0x00, 0x0d, 0x00, 0x0a, 0x00, 0x61, 0x00, 0x75, 0x00,
	0x64, 0x00, 0x69, 0x00, 0x6f, 0x00, 0x6d, 0x00, 0x6f, 0x00, 0x64, 0x00,
	0x65, 0x00, 0x3a, 0x00, 0x69, 0x00, 0x3a, 0x00, 0x30, 0x00, 0x0d, 0x00,
	0x0a, 0x00, 0x72, 0x00, 0x65, 0x00, 0x64, 0x00, 0x69, 0x00, 0x72, 0x00,
	0x65, 0x00, 0x63, 0x00, 0x74, 0x00, 0x70, 0x00, 0x72, 0x00, 0x69, 0x00,
	0x6e, 0x00, 0x74, 0x00, 0x65, 0x00, 0x72, 0x00, 0x73, 0x00, 0x3a, 0x00,
	0x69, 0x00, 0x3a, 0x00, 0x31, 0x00, 0x0d, 0x00, 0x0a, 0x00, 0x72, 0x00,
	0x65, 0x00, 0x64, 0x00, 0x69, 0x00, 0x72, 0x00, 0x65, 0x00, 0x63, 0x00,
	0x74, 0x00, 0x63, 0x00, 0x6f, 0x00, 0x6d, 0x00, 0x70, 0x00, 0x6f, 0x00,
	0x72, 0x00, 0x74, 0x00, 0x73, 0x00, 0x3a, 0x00, 0x69, 0x00, 0x3a, 0x00,
	0x30, 0x00, 0x0d, 0x00, 0x0a, 0x00, 0x72, 0x00, 0x65, 0x00, 0x64, 0x00,
	0x69, 0x00, 0x72, 0x00, 0x65, 0x00, 0x63, 0x00, 0x74, 0x00, 0x73, 0x00,
	0x6d, 0x00, 0x61, 0x00, 0x72, 0x00, 0x74, 0x00, 0x63, 0x00, 0x61, 0x00,
	0x72, 0x00, 0x64, 0x00, 0x73, 0x00, 0x3a, 0x00, 0x69, 0x00, 0x3a, 0x00,
	0x31, 0x00, 0x0d, 0x00, 0x0a, 0x00, 0x72, 0x00, 0x65, 0x00, 0x64, 0x00,
	0x69, 0x00, 0x72, 0x00, 0x65, 0x00, 0x63, 0x00, 0x74, 0x00, 0x63, 0x00,
	0x6c, 0x00, 0x69, 0x00, 0x70, 0x00, 0x62, 0x00, 0x6f, 0x00, 0x61, 0x00,
	0x72, 0x00, 0x64, 0x00, 0x3a, 0x00, 0x69, 0x00, 0x3a, 0x00, 0x31, 0x00,
	0x0d, 0x00, 0x0a, 0x00, 0x72, 0x00, 0x65, 0x00, 0x64, 0x00, 0x69, 0x00,
	0x72, 0x00, 0x65, 0x00, 0x63, 0x00, 0x74, 0x00, 0x70, 0x00, 0x6f, 0x00,
	0x73, 0x00, 0x64, 0x00, 0x65, 0x00, 0x76, 0x00, 0x69, 0x00, 0x63, 0x00,
	0x65, 0x00, 0x73, 0x00, 0x3a, 0x00, 0x69, 0x00, 0x3a, 0x00, 0x30, 0x00,
	0x0d, 0x00, 0x0a, 0x00, 0x61, 0x00, 0x75, 0x00, 0x74, 0x00, 0x6f, 0x00,
	0x72, 0x00, 0x65, 0x00, 0x63, 0x00, 0x6f, 0x00, 0x6e, 0x00, 0x6e, 0x00,
	0x65, 0x00, 0x63, 0x00, 0x74, 0x00, 0x69, 0x00, 0x6f, 0x00, 0x6e, 0x00,
	0x20, 0x00, 0x65, 0x00, 0x6e, 0x00, 0x61, 0x00, 0x62, 0x00, 0x6c, 0x00,
	0x65, 0x00, 0x64, 0x00, 0x3a, 0x00, 0x69, 0x00, 0x3a, 0x00, 0x31, 0x00,
	0x0d, 0x00, 0x0a, 0x00, 0x61, 0x00, 0x75, 0x00, 0x74, 0x00, 0x68, 0x00,
	0x65, 0x00, 0x6e, 0x00, 0x74, 0x00, 0x69, 0x00, 0x63, 0x00, 0x61, 0x00,
	0x74, 0x00, 0x69, 0x00, 0x6f, 0x00, 0x6e, 0x00, 0x20, 0x00, 0x6c, 0x00,
	0x65, 0x00, 0x76, 0x00, 0x65, 0x00, 0x6c, 0x00, 0x3a, 0x00, 0x69, 0x00,
	0x3a, 0x00, 0x32, 0x00, 0x0d, 0x00, 0x0a, 0x00, 0x70, 0x00, 0x72, 0x00,
	0x6f, 0x00, 0x6d, 0x00, 0x70, 0x00, 0x74, 0x00, 0x20, 0x00, 0x66, 0x00,
	0x6f, 0x00, 0x72, 0x00, 0x20, 0x00, 0x63, 0x00, 0x72, 0x00, 0x65, 0x00,
	0x64, 0x00, 0x65, 0x00, 0x6e, 0x00, 0x74, 0x00, 0x69, 0x00, 0x61, 0x00,
	0x6c, 0x00, 0x73, 0x00, 0x3a, 0x00, 0x69, 0x00, 0x3a, 0x00, 0x30, 0x00,
	0x0d, 0x00, 0x0a, 0x00, 0x6e, 0x00, 0x65, 0x00, 0x67, 0x00, 0x6f, 0x00,
	0x74, 0x00, 0x69, 0x00, 0x61, 0x00, 0x74, 0x00, 0x65, 0x00, 0x20, 0x00,
	0x73, 0x00, 0x65, 0x00, 0x63, 0x00, 0x75, 0x00, 0x72, 0x00, 0x69, 0x00,
	0x74, 0x00, 0x79, 0x00, 0x20, 0x00, 0x6c, 0x00, 0x61, 0x00, 0x79, 0x00,
	0x65, 0x00, 0x72, 0x00, 0x3a, 0x00, 0x69, 0x00, 0x3a, 0x00, 0x31, 0x00,
	0x0d, 0x00, 0x0a, 0x00, 0x72, 0x00, 0x65, 0x00, 0x6d, 0x00, 0x6f, 0x00,
	0x74, 0x00, 0x65, 0x00, 0x61, 0x00, 0x70, 0x00, 0x70, 0x00, 0x6c, 0x00,
	0x69, 0x00, 0x63, 0x00, 0x61, 0x00, 0x74, 0x00, 0x69, 0x00, 0x6f, 0x00,
	0x6e, 0x00, 0x6d, 0x00, 0x6f, 0x00, 0x64, 0x00, 0x65, 0x00, 0x3a, 0x00,
	0x69, 0x00, 0x3a, 0x00, 0x30, 0x00, 0x0d, 0x00, 0x0a, 0x00, 0x61, 0x00,
	0x6c, 0x00, 0x74, 0x00, 0x65, 0x00, 0x72, 0x00, 0x6e, 0x00, 0x61, 0x00,
	0x74, 0x00, 0x65, 0x00, 0x20, 0x00, 0x73, 0x00, 0x68, 0x00, 0x65, 0x00,
	0x6c, 0x00, 0x6c, 0x00, 0x3a, 0x00, 0x73, 0x00, 0x3a, 0x00, 0x0d, 0x00,
	0x0a, 0x00, 0x73, 0x00, 0x68, 0x00, 0x65, 0x00, 0x6c, 0x00, 0x6c, 0x00,
	0x20, 0x00, 0x77, 0x00, 0x6f, 0x00, 0x72, 0x00, 0x6b, 0x00, 0x69, 0x00,
	0x6e, 0x00, 0x67, 0x00, 0x20, 0x00, 0x64, 0x00, 0x69, 0x00, 0x72, 0x00,
	0x65, 0x00, 0x63, 0x00, 0x74, 0x00, 0x6f, 0x00, 0x72, 0x00, 0x79, 0x00,
	0x3a, 0x00, 0x73, 0x00, 0x3a, 0x00, 0x0d, 0x00, 0x0a, 0x00, 0x67, 0x00,
	0x61, 0x00, 0x74, 0x00, 0x65, 0x00, 0x77, 0x00, 0x61, 0x00, 0x79, 0x00,
	0x68, 0x00, 0x6f, 0x00, 0x73, 0x00, 0x74, 0x00, 0x6e, 0x00, 0x61, 0x00,
	0x6d, 0x00, 0x65, 0x00, 0x3a, 0x00, 0x73, 0x00, 0x3a, 0x00, 0x4c, 0x00,
	0x41, 0x00, 0x42, 0x00, 0x31, 0x00, 0x2d, 0x00, 0x57, 0x00, 0x32, 0x00,
	0x4b, 0x00, 0x38, 0x00, 0x52, 0x00, 0x32, 0x00, 0x2d, 0x00, 0x47, 0x00,
	0x57, 0x00, 0x2e, 0x00, 0x6c, 0x00, 0x61, 0x00, 0x62, 0x00, 0x31, 0x00,
	0x2e, 0x00, 0x61, 0x00, 0x77, 0x00, 0x61, 0x00, 0x6b, 0x00, 0x65, 0x00,
	0x2e, 0x00, 0x6c, 0x00, 0x6f, 0x00, 0x63, 0x00, 0x61, 0x00, 0x6c, 0x00,
	0x0d, 0x00, 0x0a, 0x00, 0x67, 0x00, 0x61, 0x00, 0x74, 0x00, 0x65, 0x00,
	0x77, 0x00, 0x61, 0x00, 0x79, 0x00, 0x75, 0x00, 0x73, 0x00, 0x61, 0x00,
	0x67, 0x00, 0x65, 0x00, 0x6d, 0x00, 0x65, 0x00, 0x74, 0x00, 0x68, 0x00,
	0x6f, 0x00, 0x64, 0x00, 0x3a, 0x00, 0x69, 0x00, 0x3a, 0x00, 0x31, 0x00,
	0x0d, 0x00, 0x0a, 0x00, 0x67, 0x00, 0x61, 0x00, 0x74, 0x00, 0x65, 0x00,
	0x77, 0x00, 0x61, 0x00, 0x79, 0x00, 0x63, 0x00, 0x72, 0x00, 0x65, 0x00,
	0x64, 0x00, 0x65, 0x00, 0x6e, 0x00, 0x74, 0x00, 0x69, 0x00, 0x61, 0x00,
	0x6c, 0x00, 0x73, 0x00, 0x73, 0x00, 0x6f, 0x00, 0x75, 0x00, 0x72, 0x00,
	0x63, 0x00, 0x65, 0x00, 0x3a, 0x00, 0x69, 0x00, 0x3a, 0x00, 0x30, 0x00,
	0x0d, 0x00, 0x0a, 0x00, 0x67, 0x00, 0x61, 0x00, 0x74, 0x00, 0x65, 0x00,
	0x77, 0x00, 0x61, 0x00, 0x79, 0x00, 0x70, 0x00, 0x72, 0x00, 0x6f, 0x00,
	0x66, 0x00, 0x69, 0x00, 0x6c, 0x00, 0x65, 0x00, 0x75, 0x00, 0x73, 0x00,
	0x61, 0x00, 0x67, 0x00, 0x65, 0x00, 0x6d, 0x00, 0x65, 0x00, 0x74, 0x00,
	0x68, 0x00, 0x6f, 0x00, 0x64, 0x00, 0x3a, 0x00, 0x69, 0x00, 0x3a, 0x00,
	0x31, 0x00, 0x0d, 0x00, 0x0a, 0x00, 0x70, 0x00, 0x72, 0x00, 0x6f, 0x00,
	0x6d, 0x00, 0x70, 0x00, 0x74, 0x00, 0x63, 0x00, 0x72, 0x00, 0x65, 0x00,
	0x64, 0x00, 0x65, 0x00, 0x6e, 0x00, 0x74, 0x00, 0x69, 0x00, 0x61, 0x00,
	0x6c, 0x00, 0x6f, 0x00, 0x6e, 0x00, 0x63, 0x00, 0x65, 0x00, 0x3a, 0x00,
	0x69, 0x00, 0x3a, 0x00, 0x31, 0x00, 0x0d, 0x00, 0x0a, 0x00, 0x75, 0x00,
	0x73, 0x00, 0x65, 0x00, 0x20, 0x00, 0x72, 0x00, 0x65, 0x00, 0x64, 0x00,
	0x69, 0x00, 0x72, 0x00, 0x65, 0x00, 0x63, 0x00, 0x74, 0x00, 0x69, 0x00,
	0x6f, 0x00, 0x6e, 0x00, 0x20, 0x00, 0x73, 0x00, 0x65, 0x00, 0x72, 0x00,
	0x76, 0x00, 0x65, 0x00, 0x72, 0x00, 0x20, 0x00, 0x6e, 0x00, 0x61, 0x00,
	0x6d, 0x00, 0x65, 0x00, 0x3a, 0x00, 0x69, 0x00, 0x3a, 0x00, 0x30, 0x00,
	0x0d, 0x00, 0x0a, 0x00, 0x72, 0x00, 0x64, 0x00, 0x67, 0x00, 0x69, 0x00,
	0x73, 0x00, 0x6b, 0x00, 0x64, 0x00, 0x63, 0x00, 0x70, 0x00, 0x72, 0x00,
	0x6f, 0x00, 0x78, 0x00, 0x79, 0x00, 0x3a, 0x00, 0x69, 0x00, 0x3a, 0x00,
	0x30, 0x00, 0x0d, 0x00, 0x0a, 0x00, 0x6b, 0x00, 0x64, 0x00, 0x63, 0x00,
	0x70, 0x00, 0x72, 0x00, 0x6f, 0x00, 0x78, 0x00, 0x79, 0x00, 0x6e, 0x00,
	0x61, 0x00, 0x6d, 0x00, 0x65, 0x00, 0x3a, 0x00, 0x73, 0x00, 0x3a, 0x00,
	0x0d, 0x00, 0x0a, 0x00, 0x64, 0x00, 0x72, 0x00, 0x69, 0x00, 0x76, 0x00,
	0x65, 0x00, 0x73, 0x00, 0x74, 0x00, 0x6f, 0x00, 0x72, 0x00, 0x65, 0x00,
	0x64, 0x00, 0x69, 0x00, 0x72, 0x00, 0x65, 0x00, 0x63, 0x00, 0x74, 0x00,
	0x3a, 0x00, 0x73, 0x00, 0x3a, 0x00, 0x2a, 0x00, 0x0d, 0x00, 0x0a, 0x00,
	0x75, 0x00, 0x73, 0x00, 0x65, 0x00, 0x72, 0x00, 0x6e, 0x00, 0x61, 0x00,
	0x6d, 0x00, 0x65, 0x00, 0x3a, 0x00, 0x73, 0x00, 0x3a, 0x00, 0x4c, 0x00,
	0x41, 0x00, 0x42, 0x00, 0x31, 0x00, 0x5c, 0x00, 0x4a, 0x00, 0x6f, 0x00,
	0x68, 0x00, 0x6e, 0x00, 0x44, 0x00, 0x6f, 0x00, 0x65, 0x00, 0x0d, 0x00,
	0x0a, 0x00
};

static char testRdpFileUTF8[] =
    "screen mode id:i:2\n"
    "use multimon:i:0\n"
    "desktopwidth:i:1920\n"
    "desktopheight:i:1080\n"
    "session bpp:i:32\n"
    "winposstr:s:0,1,553,211,1353,811\n"
    "compression:i:1\n"
    "keyboardhook:i:2\n"
    "audiocapturemode:i:0\n"
    "videoplaybackmode:i:1\n"
    "connection type:i:7\n"
    "networkautodetect:i:1\n"
    "bandwidthautodetect:i:1\n"
    "displayconnectionbar:i:1\n"
    "enableworkspacereconnect:i:0\n"
    "disable wallpaper:i:0\n"
    "allow font smoothing:i:0\n"
    "allow desktop composition:i:0\n"
    "disable full window drag:i:1\n"
    "disable menu anims:i:1\n"
    "disable themes:i:0\n"
    "disable cursor setting:i:0\n"
    "bitmapcachepersistenable:i:1\n"
    "full address:s:LAB1-W7-DM-01.lab1.awake.local\n"
    "alternate full address:s:LAB1-W7-DM-01.lab1.awake.global\n"
    "audiomode:i:0\n"
    "redirectprinters:i:1\n"
    "redirectcomports:i:0\n"
    "redirectsmartcards:i:1\n"
    "redirectclipboard:i:1\n"
    "redirectposdevices:i:0\n"
    "autoreconnection enabled:i:1\n"
    "authentication level:i:2\n"
    "prompt for credentials:i:0\n"
    "negotiate security layer:i:1\n"
    "remoteapplicationmode:i:0\n"
    "alternate shell:s:\n"
    "shell working directory:s:\n"
    "gatewayhostname:s:LAB1-W2K8R2-GW.lab1.awake.local\n"
    "gatewayusagemethod:i:1\n"
    "gatewaycredentialssource:i:0\n"
    "gatewayprofileusagemethod:i:1\n"
    "promptcredentialonce:i:1\n"
    "use redirection server name:i:0\n"
    "rdgiskdcproxy:i:0\n"
    "kdcproxyname:s:\n"
    "drivestoredirect:s:*\n"
    "username:s:LAB1\\JohnDoe\n"
    "vendor integer:i:123\n"
    "vendor string:s:microsoft\n";

static char* append(const char* fmt, ...)
{
	int rc;
	char* dst;
	va_list ap;

	va_start(ap, fmt);
	rc = vsnprintf(NULL, 0, fmt, ap);
	va_end(ap);
	if (rc < 0)
		return NULL;
	dst = malloc((size_t)rc + 1);
	if (!dst)
		return NULL;

	va_start(ap, fmt);
	rc = vsnprintf(dst, (size_t)rc + 1, fmt, ap);
	va_end(ap);
	if (rc < 0)
	{
		free(dst);
		return NULL;
	}
	return dst;
}

int TestClientRdpFile(int argc, char* argv[])
{
	int rc = -1;
	int iValue;
	const char* sValue;
	char* utfname = NULL;
	char* uniname = NULL;
	char* base = NULL;
	char* tmp = NULL;
	UINT64 id;
	rdpFile* file;
	rdpSettings* settings;

	WINPR_UNUSED(argc);
	WINPR_UNUSED(argv);
	winpr_RAND((BYTE*)&id, sizeof(id));

	/* Unicode */
	file = freerdp_client_rdp_file_new();
	settings = freerdp_settings_new(0);

	if (!file || !settings)
	{
		printf("rdp_file_new failed\n");
		goto fail;
	}

	if (!freerdp_client_parse_rdp_file_buffer(file, testRdpFileUTF16, sizeof(testRdpFileUTF16)))
		goto fail;

	if (!freerdp_client_populate_settings_from_rdp_file(file, settings))
		goto fail;

	if (settings->UseMultimon)
	{
		printf("UseMultiMon mismatch: Actual: %"PRIu32", Expected: 0\n", settings->UseMultimon);
		goto fail;
	}

	if (!settings->Fullscreen)
	{
		printf("ScreenModeId mismatch: Actual: %"PRIu32", Expected: TRUE\n", settings->Fullscreen);
		goto fail;
	}

#if 0 /* TODO: Currently unused */
	if (settings->GatewayProfileUsageMethod != 1)
	{
		printf("GatewayProfileUsageMethod mismatch: Actual: %"PRIu32", Expected: 1\n",
			   settings->GatewayProfileUsageMethod);
		goto fail;
	}
#endif

	if (strcmp(settings->GatewayHostname, "LAB1-W2K8R2-GW.lab1.awake.local") != 0)
	{
		printf("GatewayHostname mismatch: Actual: %s, Expected: %s\n",
			   settings->GatewayHostname, "LAB1-W2K8R2-GW.lab1.awake.local");
		goto fail;
	}

	if (strcmp(settings->ServerHostname, "LAB1-W7-DM-01.lab1.awake.local") != 0)
	{
		printf("ServerHostname mismatch: Actual: %s, Expected: %s\n",
			   settings->ServerHostname, "LAB1-W7-DM-01.lab1.awake.local");
		goto fail;
	}

	freerdp_client_rdp_file_free(file);
	freerdp_settings_free(settings);
	/* Ascii */
	file = freerdp_client_rdp_file_new();
	settings = freerdp_settings_new(0);
	if (!file || !settings)
	{
		printf("rdp_file_new failed\n");
		goto fail;
	}

	if (!freerdp_client_parse_rdp_file_buffer(file, (BYTE*) testRdpFileUTF8, sizeof(testRdpFileUTF8)))
		goto fail;

	if (!freerdp_client_populate_settings_from_rdp_file(file, settings))
		goto fail;

	if (settings->UseMultimon != 0)
	{
		printf("UseMultiMon mismatch: Actual: %"PRIu32", Expected: 0\n", settings->UseMultimon);
		return -1;
	}

	if (!settings->Fullscreen)
	{
		printf("ScreenModeId mismatch: Actual: %"PRIu32", Expected: TRUE\n", settings->Fullscreen);
		return -1;
	}

#if 0 /* TODO: Currently unused */
	if (settings->GatewayProfileUsageMethod != 1)
	{
		printf("GatewayProfileUsageMethod mismatch: Actual: %"PRIu32", Expected: 1\n",
			   settings->GatewayProfileUsageMethod);
		goto fail;
	}
#endif

	if (strcmp(settings->ServerHostname, "LAB1-W7-DM-01.lab1.awake.global") != 0)
	{
		printf("ServerHostname mismatch: Actual: %s, Expected: %s\n",
			   settings->ServerHostname, "LAB1-W7-DM-01.lab1.awake.global");
		goto fail;
	}

	if (strcmp(settings->GatewayHostname, "LAB1-W2K8R2-GW.lab1.awake.local") != 0)
	{
		printf("GatewayHostname mismatch: Actual: %s, Expected: %s\n",
			   settings->GatewayHostname, "LAB1-W2K8R2-GW.lab1.awake.local");
		goto fail;
	}

	iValue = freerdp_client_rdp_file_get_integer_option(file, "vendor integer");
	if (iValue != 123)
		goto fail;

	if (freerdp_client_rdp_file_set_integer_option(file, "vendor integer", 456) == -1)
	{
		printf("failed to set integer: vendor integer");
		goto fail;
	}

	iValue = freerdp_client_rdp_file_get_integer_option(file, "vendor integer");
	if (iValue != 456)
		return -1;

	sValue = freerdp_client_rdp_file_get_string_option(file, "vendor string");
	if (strncmp(sValue, "microsoft", 10) != 0)
		goto fail;

	freerdp_client_rdp_file_set_string_option(file, "vendor string", "apple");
	sValue = freerdp_client_rdp_file_get_string_option(file, "vendor string");
	if (strncmp(sValue, "apple", 6) != 0)
		goto fail;

	freerdp_client_rdp_file_set_string_option(file, "fruits", "banana,oranges");

	if (freerdp_client_rdp_file_set_integer_option(file, "numbers", 123456789) == -1)
	{
		printf("failed to set integer: numbers");
		return -1;
	}

	freerdp_client_rdp_file_free(file);

	tmp = GetKnownPath(KNOWN_PATH_TEMP);
	if (!tmp)
		goto fail;

	base = append("%s/rdp-file-test-%"PRIx64, tmp, id);
	if (!base)
		goto fail;
	if (!CreateDirectoryA(base, NULL))
		goto fail;
	utfname = append("%s/utfname", base);
	uniname = append("%s/uniname", base);
	file = freerdp_client_rdp_file_new();
	if (!file || !utfname || !uniname)
		goto fail;

	if (!freerdp_client_populate_rdp_file_from_settings(file, settings))
		goto fail;

	if (!freerdp_client_write_rdp_file(file, utfname, FALSE))
		goto fail;

	if (!freerdp_client_write_rdp_file(file,  uniname, TRUE))
		goto fail;

	rc = 0;
fail:
	if (utfname)
		DeleteFileA(utfname);
	if (uniname)
		DeleteFileA(uniname);
	if (base)
		RemoveDirectoryA(base);
	free(utfname);
	free(uniname);
	free(base);
	free(tmp);
	freerdp_client_rdp_file_free(file);
	freerdp_settings_free(settings);
	return rc;
}
