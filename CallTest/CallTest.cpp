
#include <iostream>
#include <Windows.h>
#pragma warning(disable:4996)

#define DIGITALPIDMAXLEN 256 



typedef enum {
	ltFPP,
	ltCCP,
	ltOEM,
	ltSelect,
	ltMLP,
	ltMOLP,
	ltMSDN
} LICENSETYPE;
typedef DWORD DWLICENSETYPE;

typedef struct {
	DWORD dwLength;
	WORD  wVersionMajor;
	WORD  wVersionMinor;
	char  szPid2[24];
	DWORD dwKeyIdx;
	char  szSku[16];
	BYTE  abCdKey[16];
	DWORD dwCloneStatus;
	DWORD dwTime;
	DWORD dwRandom;
	DWLICENSETYPE dwlt;
	DWORD adwLicenseData[2];
	char  szOemId[8];
	DWORD dwBundleId;

	char  aszHardwareIdStatic[8];

	DWORD dwHardwareIdTypeStatic;
	DWORD dwBiosChecksumStatic;
	DWORD dwVolSerStatic;
	DWORD dwTotalRamStatic;
	DWORD dwVideoBiosChecksumStatic;

	char  aszHardwareIdDynamic[8];

	DWORD dwHardwareIdTypeDynamic;
	DWORD dwBiosChecksumDynamic;
	DWORD dwVolSerDynamic;
	DWORD dwTotalRamDynamic;
	DWORD dwVideoBiosChecksumDynamic;

	DWORD dwCrc32;
} DIGITALPID, * PDIGITALPID, FAR* LPDIGITALPID;

typedef BOOL(WINAPI* DelegatePIDGenA)(LPSTR   lpstrSecureCdKey, LPCSTR  lpstrMpc, LPCSTR  lpstrSku, LPCSTR  lpstrOemId, LPSTR   lpstrLocal24, LPBYTE  lpbPublicKey, DWORD   dwcbPublicKey, DWORD   dwKeyIdx, BOOL    fOem, LPSTR   lpstrPid2, LPBYTE  lpbDigPid, LPDWORD lpdwSeq, LPBOOL  pfCCP, LPBOOL  pfPSS);
typedef BOOL(WINAPI* DelegatePIDGenSimpA)(LPSTR   lpstrSecureCdKey, LPCSTR  lpstrMpc, LPCSTR  lpstrSku, LPCSTR  lpstrOemId, BOOL    fOem, LPSTR   lpstrPid2, LPBYTE  lpbDigPid, LPDWORD lpdwSeq, LPBOOL  pfCCP);
typedef BOOL(WINAPI* DelegateSetupPIDGenA)(LPSTR   lpstrSecureCdKey, LPCSTR  lpstrRpc, LPCSTR  lpstrSku, BOOL    fOem, struct  _PID2*  lpstrPid2, struct _DPID3* lpbPid3, LPBOOL  pfCCP);


char  achPid2[32];
BYTE  abPid3[DIGITALPIDMAXLEN];
LPDIGITALPID pdp = (LPDIGITALPID)abPid3;

int main()
{
	HMODULE hModule = LoadLibrary(L".\\pidgen.dll");
	if (!hModule)
	{
		printf("[!] LoadLibraryA failed. Error: %d\n", GetLastError());
		return 0;
	}
	DelegateSetupPIDGenA pSetupPIDGenA = (DelegateSetupPIDGenA)GetProcAddress(hModule, "SetupPIDGenA");
	DelegatePIDGenSimpA pPIDGenSimpA = (DelegatePIDGenSimpA)GetProcAddress(hModule, "PIDGenSimpA");
	DelegatePIDGenA pPIDGenA = (DelegatePIDGenA)GetProcAddress(hModule, "PIDGenA");


	*(LPDWORD)abPid3 = sizeof(abPid3);
	const char*  lpszProductKey = "GRHQ2-CDPWX-WWJBT-RXWFG-6CXCT";
	BOOL result = pPIDGenA((LPSTR)lpszProductKey, "xxxxx", "xxx-xxxxx", "MSFT", NULL, NULL, 0, 0, FALSE, achPid2, abPid3, 0, FALSE, FALSE);
	if (result)
	{
		MessageBoxA(NULL, "Done", "Done!", MB_OK);
	}
	else
	{
		MessageBoxA(NULL, "Error", "Error!", MB_OK);
	}

}


