/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRMRESULTS_H__
#define __DRMRESULTS_H__

/*
** This file contains all the DRM_RESULTS required for building Porting Kit
** applications.
**
** NOTE: PC and Services error codes should ****NOT**** be added here, 
**       but rather to the files discussed in the comments further down
**       regarding them.
**
** NOTE: DRM_RESULTS can be converted into Windows HRESULTS without any
**       changes. The FACILITY values below are carefully selected to allow
**       for this.
**
*/

#if SIXTEEN_BIT_ADDRESSING
#define DRM_FAILED(Status) (((DRM_RESULT)(Status)&0x80000000)!=0)
#define DRM_SUCCEEDED(Status) (((DRM_RESULT)(Status)&0x80000000)==0)
#else
#define DRM_FAILED(Status) ((DRM_RESULT)(Status)<0)
#define DRM_SUCCEEDED(Status) ((DRM_RESULT)(Status) >= 0)
#endif

#define DRM_S_BASECODE                          0xC000
#define DRM_E_BASECODE                          0xC000
#define DRM_E_PK_BASECODE                       0xA000


/*
*  !!!!!!  VERY IMPORTANT, PLEASE READ !!!!!
*
*   There's a range of error codes that is only applicable to the PC and should
*   not be included here. These errors are in common\include, files:
*   msprerr.h
*   drmndbridgeerr.h
*   errorservice.h
*   To prevent overlaps of PK and PC error codes, please assume that:
*   The range from 0x8004B000 to 0x8004BEFF is reserved for the PC (error codes).
*   The range from 0x0004B000 to 0x0004BEFF is reserved for the PC (success codes).
*   The range from 0x8004BE00 to 0x8004BFFF is reserved for the Modern SDK (error codes).
*   The range from 0x0004BE00 to 0x0004BFFF is reserved for the Modern SDK (success codes).
*   The following three defines represent the basecodes for the PC.
*/
#define DRM_E_NDBRIDGEONLY_BASECODE     0xB000
#define DRM_E_MSPRSDK_BASECODE          0xB800
#define DRM_E_MODERN_BASECODE           0xBE00

#define DRM_FACILITY_ITF DRM_FACILITY_CORE

#define MAKE_DRM_RESULT(sev,fac,code) \
    ((DRM_RESULT) (((unsigned long)(sev)<<30) | ((unsigned long)(fac)<<16) | ((unsigned long)(code))) )

/* ============================================================
**
** Standard Success values
**
** ============================================================
*/

/*
 *  Values are 32 bit values laid out as follows:
 *
 *   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
 *   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 *  +-+-+-+-+-+---------------------+-------------------------------+
 *  |S|R|C|N|r|    Facility         |               Code            |
 *  +-+-+-+-+-+---------------------+-------------------------------+
 *
 *  where
 *
 *      S - Severity - indicates success/fail
 *
 *          0 - Success
 *          1 - Fail (COERROR)
 *
 *      R - reserved portion of the facility code, corresponds to NT's
 *              second severity bit.
 *
 *      C - reserved portion of the facility code, corresponds to NT's
 *              C field.
 *
 *      N - reserved portion of the facility code. Used to indicate a
 *              mapped NT status value.
 *
 *      r - reserved portion of the facility code. Reserved for internal
 *              use. Used to indicate HRESULT values that are not status
 *              values, but are instead message ids for display strings.
 *
 *      Facility - is the facility code
 *
 *      Code - is the facility's status code
 *
 *
 * Define the facility codes
 *
 */
#define DRM_FACILITY_WIN32               0x7
#define DRM_FACILITY_STANDARD            0x0
#define DRM_FACILITY_NETSHOW             0xD
#define DRM_FACILITY_CORE                0x4
#define DRM_FACILITY_COM_STORAGE         0x3


/*
 * Define the severity codes
 *
 */
#define DRM_SEVERITY_SUCCESS             0x0
#define DRM_SEVERITY_NETSHOW_ERROR       0x3
#define DRM_SEVERITY_ERROR               0x2


/*
 * MessageId: DRM_SUCCESS
 *
 * MessageText:
 *
 * Operation was successful.
 *
 */
#define DRM_SUCCESS                      ((DRM_RESULT)0x00000000L)

/*
 * MessageId: DRM_S_FALSE
 *
 * MessageText:
 *
 * Operation was successful, but returned a FALSE test condition.
 *
 */
#define DRM_S_FALSE                      ((DRM_RESULT)0x00000001L)

/*
 * MessageId: DRM_S_MORE_DATA
 *
 * MessageText:
 *
 * Operation was successful, but more data is available.
 *
 */
#define DRM_S_MORE_DATA                  ((DRM_RESULT)0x00000002L)



/* ============================================================
**
** Standard error messages (0x8000xxxx)
**
** ============================================================
*/

/*
 * MessageId: DRM_E_OUTOFMEMORY
 *
 * MessageText:
 *
 * Insufficient resources exist to complete the request.
 *
 */
#define DRM_E_OUTOFMEMORY                ((DRM_RESULT)0x80000002L)

/*
 * MessageId: DRM_E_NOTIMPL
 *
 * MessageText:
 *
 * The requested operation is not implemented.
 *
 */
#define DRM_E_NOTIMPL                    ((DRM_RESULT)0x80004001L)

/*
 * MessageId: DRM_E_POINTER
 *
 * MessageText:
 *
 * Invalid pointer.
 *
 */
#define DRM_E_POINTER                    ((DRM_RESULT)0x80004003L)

/*
 * MessageId: DRM_E_FAIL
 *
 * MessageText:
 *
 * The requested operation failed.
 *
 */
#define DRM_E_FAIL                       ((DRM_RESULT)0x80004005L)


/* ============================================================
**
** Error messages shared with Win32 (0x8007xxxx)
**
** ============================================================
*/

/*
 * MessageId: DRM_E_WIN32_FILE_NOT_FOUND
 *
 * MessageText:
 *
 * The system cannot find the file specified.
 *
 */
#define DRM_E_WIN32_FILE_NOT_FOUND       ((DRM_RESULT)0x80070002L)

/*
 * MessageId: DRM_E_HANDLE
 *
 * MessageText:
 *
 * Invalid handle.
 *
 */
#define DRM_E_HANDLE                     ((DRM_RESULT)0x80070006L)

/*
 * MessageId: DRM_E_WIN32_NO_MORE_FILES
 *
 * MessageText:
 *
 * There are no more files.
 *
 */
#define DRM_E_WIN32_NO_MORE_FILES        ((DRM_RESULT)0x80070012L)

/*
 * MessageId: DRM_E_INVALIDARG
 *
 * MessageText:
 *
 * The parameter is incorrect.
 *
 */
#define DRM_E_INVALIDARG                 ((DRM_RESULT)0x80070057L)

/*
 * MessageId: DRM_E_BUFFERTOOSMALL
 *
 * MessageText:
 *
 * The data area passed to a function is too small.
 *
 */
#define DRM_E_BUFFERTOOSMALL             ((DRM_RESULT)0x8007007AL)

/*
 * MessageId: DRM_E_NOMORE
 *
 * MessageText:
 *
 * No more data is available.
 *
 */
#define DRM_E_NOMORE                     ((DRM_RESULT)0x80070103L)

/*
 * MessageId: DRM_E_ARITHMETIC_OVERFLOW
 *
 * MessageText:
 *
 * Arithmetic result exceeded maximum value.
 *
 */
#define DRM_E_ARITHMETIC_OVERFLOW        ((DRM_RESULT)0x80070216L)

/*
 * MessageId: DRM_E_NOT_FOUND
 *
 * MessageText:
 *
 * Element not found.
 *
 */
#define DRM_E_NOT_FOUND                  ((DRM_RESULT)0x80070490L)

/*
 * MessageId: DRM_E_INVALID_COMMAND_LINE
 *
 * MessageText:
 *
 * Invalid command line argument.
 *
 */
#define DRM_E_INVALID_COMMAND_LINE       ((DRM_RESULT)0x80070667L)


/* ============================================================
**
** Error messages shared with COM Storage (mostly file errors)
** (0x8003xxxx)
**
** ============================================================
*/

/*
 * MessageId: DRM_E_FILENOTFOUND
 *
 * MessageText:
 *
 * A requested file could not be found.
 *
 */
#define DRM_E_FILENOTFOUND               ((DRM_RESULT)0x80030002L)

/*
 * MessageId: DRM_E_FILEOPEN
 *
 * MessageText:
 *
 * A request failed due to a file being open.
 *
 */
#define DRM_E_FILEOPEN                   ((DRM_RESULT)0x8003006EL)


/* ============================================================
**
** NetShow Errors from NsError.h (0xc00Dxxxx)
**
** ============================================================
*/

/*
 * MessageId: DRM_E_PARAMETERS_MISMATCHED
 *
 * MessageText:
 *
 * A problem has occurred in the Digital Rights Management component.
 *
 */
#define DRM_E_PARAMETERS_MISMATCHED      ((DRM_RESULT)0xC00D272FL)

/*
 * MessageId: DRM_E_FAILED_TO_STORE_LICENSE
 *
 * MessageText:
 *
 * License storage is not working.
 *
 */
#define DRM_E_FAILED_TO_STORE_LICENSE    ((DRM_RESULT)0xC00D2712L)

/*
 * MessageId: DRM_E_NOT_ALL_STORED
 *
 * MessageText:
 *
 * Some of the licenses could not be stored.
 *
 */
#define DRM_E_NOT_ALL_STORED             ((DRM_RESULT)0xC00D275FL)


/* ============================================================
**
** Vista crypto errors, 0x80040e80-0x80040e8f.
**
** ============================================================
*/

/*
 * MessageId: DRM_E_VERIFICATION_FAILURE
 *
 * MessageText:
 *
 * Validation of a Longhorn certificate failed.
 *
 */
#define DRM_E_VERIFICATION_FAILURE       ((DRM_RESULT)0x80040E80L)

/*
 * MessageId: DRM_E_RSA_SIGNATURE_ERROR
 *
 * MessageText:
 *
 * Error in RSA(PSS) signature.
 *
 */
#define DRM_E_RSA_SIGNATURE_ERROR        ((DRM_RESULT)0x80040E82L)

/*
 * MessageId: DRM_E_BAD_RSA_EXPONENT
 *
 * MessageText:
 *
 * An incorrect RSA exponent was supplied for a public key.
 *
 */
#define DRM_E_BAD_RSA_EXPONENT           ((DRM_RESULT)0x80040E86L)

/*
 * MessageId: DRM_E_P256_CONVERSION_FAILURE
 *
 * MessageText:
 *
 * An error occurred while converting between P256 types.
 *
 */
#define DRM_E_P256_CONVERSION_FAILURE    ((DRM_RESULT)0x80040E87L)

/*
 * MessageId: DRM_E_P256_PKCRYPTO_FAILURE
 *
 * MessageText:
 *
 * An error occurred in an asymmetric P256 cryptographic operation.
 *
 */
#define DRM_E_P256_PKCRYPTO_FAILURE      ((DRM_RESULT)0x80040E88L)

/*
 * MessageId: DRM_E_P256_PLAINTEXT_MAPPING_FAILURE
 *
 * MessageText:
 *
 * An error occurred while attempting to map a plaintext array to a EC Point: There is no conversion for this byte array to a EC Point.
 *
 */
#define DRM_E_P256_PLAINTEXT_MAPPING_FAILURE ((DRM_RESULT)0x80040E89L)

/*
 * MessageId: DRM_E_P256_INVALID_SIGNATURE
 *
 * MessageText:
 *
 * The ECDSA signature to be verified was not a valid signature format.
 *
 */
#define DRM_E_P256_INVALID_SIGNATURE     ((DRM_RESULT)0x80040E8AL)

/*
 * MessageId: DRM_E_P256_ECDSA_VERIFICATION_ERROR
 *
 * MessageText:
 *
 * The ECDSA verification algorithm encountered an unknown error.
 *
 */
#define DRM_E_P256_ECDSA_VERIFICATION_ERROR ((DRM_RESULT)0x80040E8BL)

/*
 * MessageId: DRM_E_P256_ECDSA_SIGNING_ERROR
 *
 * MessageText:
 *
 * The ECDSA signature algorithm encountered an unknown error.
 *
 */
#define DRM_E_P256_ECDSA_SIGNING_ERROR   ((DRM_RESULT)0x80040E8CL)

/*
 * MessageId: DRM_E_P256_HMAC_KEYGEN_FAILURE
 *
 * MessageText:
 *
 * Could not generate a valid HMAC key under constraint where CK || HMACK is a valid x coord on the EC (P256).
 *
 */
#define DRM_E_P256_HMAC_KEYGEN_FAILURE   ((DRM_RESULT)0x80040E8DL)


/* ============================================================
**
** IContentHeader errors: error codes from DRM_E_CH_BASECODE+0
** to DRM_E_CH_BASECODE+0xFF, 0x80041100-0x800411ff.
**
** ============================================================
*/

#define DRM_E_CH_BASECODE                ((DRM_RESULT)0x80041100L)

/*
 * MessageId: DRM_E_CH_VERSION_MISSING
 *
 * MessageText:
 *
 * Missing content header version.
 *
 */
#define DRM_E_CH_VERSION_MISSING         ((DRM_RESULT)0x80041103L)

/*
 * MessageId: DRM_E_CH_KID_MISSING
 *
 * MessageText:
 *
 * Missing KID attribute in content header.
 *
 */
#define DRM_E_CH_KID_MISSING             ((DRM_RESULT)0x80041104L)

/*
 * MessageId: DRM_E_CH_LAINFO_MISSING
 *
 * MessageText:
 *
 * Missing LAINFO attribute in content header.
 *
 */
#define DRM_E_CH_LAINFO_MISSING          ((DRM_RESULT)0x80041105L)

/*
 * MessageId: DRM_E_CH_CHECKSUM_MISSING
 *
 * MessageText:
 *
 * Missing content header checksum.
 *
 */
#define DRM_E_CH_CHECKSUM_MISSING        ((DRM_RESULT)0x80041106L)

/*
 * MessageId: DRM_E_CH_ATTR_MISSING
 *
 * MessageText:
 *
 * Missing content header attribute.
 *
 */
#define DRM_E_CH_ATTR_MISSING            ((DRM_RESULT)0x80041107L)

/*
 * MessageId: DRM_E_CH_INVALID_HEADER
 *
 * MessageText:
 *
 * Invalid content header.
 *
 */
#define DRM_E_CH_INVALID_HEADER          ((DRM_RESULT)0x80041108L)

/*
 * MessageId: DRM_E_CH_INVALID_CHECKSUM
 *
 * MessageText:
 *
 * Invalid checksum in the header.
 *
 */
#define DRM_E_CH_INVALID_CHECKSUM        ((DRM_RESULT)0x80041109L)

/*
 * MessageId: DRM_E_CH_UNABLE_TO_VERIFY
 *
 * MessageText:
 *
 * Unable to verify signature of content header.
 *
 */
#define DRM_E_CH_UNABLE_TO_VERIFY        ((DRM_RESULT)0x8004110AL)

/*
 * MessageId: DRM_E_CH_UNSUPPORTED_VERSION
 *
 * MessageText:
 *
 * Unsupported content header version.
 *
 */
#define DRM_E_CH_UNSUPPORTED_VERSION     ((DRM_RESULT)0x8004110BL)

/*
 * MessageId: DRM_E_CH_BAD_KEY
 *
 * MessageText:
 *
 * Invalid key.
 *
 */
#define DRM_E_CH_BAD_KEY                 ((DRM_RESULT)0x8004110EL)

/*
 * MessageId: DRM_E_CH_INCOMPATIBLE_HEADER_TYPE
 *
 * MessageText:
 *
 * Incompatible content header type.
 *
 */
#define DRM_E_CH_INCOMPATIBLE_HEADER_TYPE ((DRM_RESULT)0x8004110FL)

/*
 * MessageId: DRM_E_HEADER_ALREADY_SET
 *
 * MessageText:
 *
 * Content header type is already set. Reinitialize is required.
 *
 */
#define DRM_E_HEADER_ALREADY_SET         ((DRM_RESULT)0x80041110L)


/* ============================================================
**
** License parsing results: error codes from 0x80041200-0x800412ff.
**
** ============================================================
*/

#define DRM_E_LIC_BASECODE           ((DRM_RESULT)0x80041200L)

/*
 * MessageId: DRM_E_LIC_PARAM_NOT_OPTIONAL
 *
 * MessageText:
 *
 *  DRM_E_LIC_PARAM_NOT_OPTIONAL
 *
 */
#define DRM_E_LIC_PARAM_NOT_OPTIONAL     ((DRM_RESULT)0x80041203L)

/*
 * MessageId: DRM_E_LIC_INVALID_LICENSE
 *
 * MessageText:
 *
 *  DRM_E_LIC_INVALID_LICENSE
 *
 */
#define DRM_E_LIC_INVALID_LICENSE        ((DRM_RESULT)0x80041205L)

/*
 * MessageId: DRM_E_LIC_UNSUPPORTED_VALUE
 *
 * MessageText:
 *
 *  DRM_E_LIC_UNSUPPORTED_VALUE
 *
 */
#define DRM_E_LIC_UNSUPPORTED_VALUE      ((DRM_RESULT)0x80041207L)


/* ============================================================
**
** Expression evaluator results: error codes from 0x80041400-0x800414ff.
**
** ============================================================
*/

#define DRM_E_CPRMEXP_BASECODE       ((DRM_RESULT)0x80041400L)

/*
 * MessageId: DRM_E_CPRMEXP_NOERROR
 *
 * MessageText:
 *
 *  DRM_E_CPRMEXP_NOERROR
 *
 */
#define DRM_E_CPRMEXP_NOERROR            ((DRM_RESULT)0x00041400L)

/*
 * MessageId: DRM_E_CPRMEXP_NO_OPERANDS_IN_EXPRESSION
 *
 * MessageText:
 *
 *  DRM_E_CPRMEXP_NO_OPERANDS_IN_EXPRESSION
 *
 */
#define DRM_E_CPRMEXP_NO_OPERANDS_IN_EXPRESSION ((DRM_RESULT)0x80041403L)

/*
 * MessageId: DRM_E_CPRMEXP_INVALID_TOKEN
 *
 * MessageText:
 *
 *  DRM_E_CPRMEXP_INVALID_TOKEN
 *
 */
#define DRM_E_CPRMEXP_INVALID_TOKEN      ((DRM_RESULT)0x80041404L)

/*
 * MessageId: DRM_E_CPRMEXP_INVALID_CONSTANT
 *
 * MessageText:
 *
 *  DRM_E_CPRMEXP_INVALID_CONSTANT
 *
 */
#define DRM_E_CPRMEXP_INVALID_CONSTANT   ((DRM_RESULT)0x80041405L)

/*
 * MessageId: DRM_E_CPRMEXP_INVALID_VARIABLE
 *
 * MessageText:
 *
 *  DRM_E_CPRMEXP_INVALID_VARIABLE
 *
 */
#define DRM_E_CPRMEXP_INVALID_VARIABLE   ((DRM_RESULT)0x80041406L)

/*
 * MessageId: DRM_E_CPRMEXP_INVALID_FUNCTION
 *
 * MessageText:
 *
 *  DRM_E_CPRMEXP_INVALID_FUNCTION
 *
 */
#define DRM_E_CPRMEXP_INVALID_FUNCTION   ((DRM_RESULT)0x80041407L)

/*
 * MessageId: DRM_E_CPRMEXP_INVALID_ARGUMENT
 *
 * MessageText:
 *
 *  DRM_E_CPRMEXP_INVALID_ARGUMENT
 *
 */
#define DRM_E_CPRMEXP_INVALID_ARGUMENT   ((DRM_RESULT)0x80041408L)

/*
 * MessageId: DRM_E_CPRMEXP_INVALID_CONTEXT
 *
 * MessageText:
 *
 *  DRM_E_CPRMEXP_INVALID_CONTEXT
 *
 */
#define DRM_E_CPRMEXP_INVALID_CONTEXT    ((DRM_RESULT)0x80041409L)

/*
 * MessageId: DRM_E_CPRMEXP_MISSING_OPERAND
 *
 * MessageText:
 *
 *  DRM_E_CPRMEXP_MISSING_OPERAND
 *
 */
#define DRM_E_CPRMEXP_MISSING_OPERAND    ((DRM_RESULT)0x8004140BL)

/*
 * MessageId: DRM_E_CPRMEXP_OVERFLOW
 *
 * MessageText:
 *
 *  DRM_E_CPRMEXP_OVERFLOW
 *
 */
#define DRM_E_CPRMEXP_OVERFLOW           ((DRM_RESULT)0x8004140CL)

/*
 * MessageId: DRM_E_CPRMEXP_UNDERFLOW
 *
 * MessageText:
 *
 *  DRM_E_CPRMEXP_UNDERFLOW
 *
 */
#define DRM_E_CPRMEXP_UNDERFLOW          ((DRM_RESULT)0x8004140DL)

/*
 * MessageId: DRM_E_CPRMEXP_INCORRECT_NUM_ARGS
 *
 * MessageText:
 *
 *  DRM_E_CPRMEXP_INCORRECT_NUM_ARGS
 *
 */
#define DRM_E_CPRMEXP_INCORRECT_NUM_ARGS ((DRM_RESULT)0x8004140EL)

/*
 * MessageId: DRM_E_CPRMEXP_VARIABLE_EXPECTED
 *
 * MessageText:
 *
 *  DRM_E_CPRMEXP_VARIABLE_EXPECTED
 *
 */
#define DRM_E_CPRMEXP_VARIABLE_EXPECTED  ((DRM_RESULT)0x8004140FL)

/*
 * MessageId: DRM_E_CPRMEXP_RETRIEVAL_FAILURE
 *
 * MessageText:
 *
 *  DRM_E_CPRMEXP_RETRIEVAL_FAILURE
 *
 */
#define DRM_E_CPRMEXP_RETRIEVAL_FAILURE  ((DRM_RESULT)0x80041410L)

/*
 * MessageId: DRM_E_CPRMEXP_UPDATE_FAILURE
 *
 * MessageText:
 *
 *  DRM_E_CPRMEXP_UPDATE_FAILURE
 *
 */
#define DRM_E_CPRMEXP_UPDATE_FAILURE     ((DRM_RESULT)0x80041411L)

/*
 * MessageId: DRM_E_CPRMEXP_STRING_UNTERMINATED
 *
 * MessageText:
 *
 *  DRM_E_CPRMEXP_STRING_UNTERMINATED
 *
 */
#define DRM_E_CPRMEXP_STRING_UNTERMINATED ((DRM_RESULT)0x80041412L)

/*
 * MessageId: DRM_E_CPRMEXP_UPDATE_UNSUPPORTED
 *
 * MessageText:
 *
 *  DRM_E_CPRMEXP_UPDATE_UNSUPPORTED
 *
 */
#define DRM_E_CPRMEXP_UPDATE_UNSUPPORTED ((DRM_RESULT)0x80041413L)

/*
 * MessageId: DRM_E_CPRMEXP_ISOLATED_OPERAND_OR_OPERATOR
 *
 * MessageText:
 *
 *  DRM_E_CPRMEXP_ISOLATED_OPERAND_OR_OPERATOR
 *
 */
#define DRM_E_CPRMEXP_ISOLATED_OPERAND_OR_OPERATOR ((DRM_RESULT)0x80041414L)

/*
 * MessageId: DRM_E_CPRMEXP_UNMATCHED
 *
 * MessageText:
 *
 *  DRM_E_CPRMEXP_UNMATCHED
 *
 */
#define DRM_E_CPRMEXP_UNMATCHED          ((DRM_RESULT)0x80041415L)

/*
 * MessageId: DRM_E_CPRMEXP_WRONG_TYPE_OPERAND
 *
 * MessageText:
 *
 *  DRM_E_CPRMEXP_WRONG_TYPE_OPERAND
 *
 */
#define DRM_E_CPRMEXP_WRONG_TYPE_OPERAND ((DRM_RESULT)0x80041416L)

/*
 * MessageId: DRM_E_CPRMEXP_TOO_MANY_OPERANDS
 *
 * MessageText:
 *
 *  DRM_E_CPRMEXP_TOO_MANY_OPERANDS
 *
 */
#define DRM_E_CPRMEXP_TOO_MANY_OPERANDS  ((DRM_RESULT)0x80041417L)

/*
 * MessageId: DRM_E_CPRMEXP_UNKNOWN_PARSE_ERROR
 *
 * MessageText:
 *
 *  DRM_E_CPRMEXP_UNKNOWN_PARSE_ERROR
 *
 */
#define DRM_E_CPRMEXP_UNKNOWN_PARSE_ERROR ((DRM_RESULT)0x80041418L)

/*
 * MessageId: DRM_E_CPRMEXP_UNSUPPORTED_FUNCTION
 *
 * MessageText:
 *
 *  DRM_E_CPRMEXP_UNSUPPORTED_FUNCTION
 *
 */
#define DRM_E_CPRMEXP_UNSUPPORTED_FUNCTION ((DRM_RESULT)0x80041419L)

/*
 * MessageId: DRM_E_CPRMEXP_CLOCK_REQUIRED
 *
 * MessageText:
 *
 *  DRM_E_CPRMEXP_CLOCK_REQUIRED
 *
 */
#define DRM_E_CPRMEXP_CLOCK_REQUIRED     ((DRM_RESULT)0x8004141AL)


/* ============================================================
**
** Legacy errors: error codes from 0x80048000-0x800480ff.
**
** ============================================================
*/

#define DRM_E_LEGACY_BASECODE                ((DRM_RESULT)0x80048000L)

/*
 * MessageId: DRM_E_LIC_KEY_DECODE_FAILURE
 *
 * MessageText:
 *
 * Key decode failure.
 *
 */
#define DRM_E_LIC_KEY_DECODE_FAILURE     ((DRM_RESULT)0x80048007L)

/*
 * MessageId: DRM_E_LIC_SIGNATURE_FAILURE
 *
 * MessageText:
 *
 * License signature failure.
 *
 */
#define DRM_E_LIC_SIGNATURE_FAILURE      ((DRM_RESULT)0x80048008L)

/*
 * MessageId: DRM_E_KEY_MISMATCH
 *
 * MessageText:
 *
 * A public/private keypair is mismatched.
 *
 */
#define DRM_E_KEY_MISMATCH               ((DRM_RESULT)0x80048014L)

/*
 * MessageId: DRM_E_INVALID_SIGNATURE
 *
 * MessageText:
 *
 * License signature failure.
 *
 */
#define DRM_E_INVALID_SIGNATURE          ((DRM_RESULT)0x800480CFL)

/*
 * MessageId: DRM_E_SYNC_ENTRY_NOT_FOUND
 *
 * MessageText:
 *
 * An entry was not found in the sync store.
 *
 */
#define DRM_E_SYNC_ENTRY_NOT_FOUND       ((DRM_RESULT)0x800480D0L)

/*
 * MessageId: DRM_E_CIPHER_NOT_INITIALIZED
 *
 * MessageText:
 *
 * The DRM Cipher routines were not correctly initialized before calling encryption/decryption routines.
 *
 */
#define DRM_E_CIPHER_NOT_INITIALIZED     ((DRM_RESULT)0x800480D2L)

/*
 * MessageId: DRM_E_DECRYPT_NOT_INITIALIZED
 *
 * MessageText:
 *
 * The DRM decrypt routines were not correctly initialized before trying to decrypt data.
 *
 */
#define DRM_E_DECRYPT_NOT_INITIALIZED    ((DRM_RESULT)0x800480D3L)

/*
 * MessageId: DRM_E_SECURESTORE_LOCK_NOT_OBTAINED
 *
 * MessageText:
 *
 * Before reading or writing data to securestore in raw mode, first the lock must be obtained using DRM_SST_OpenData.
 *
 */
#define DRM_E_SECURESTORE_LOCK_NOT_OBTAINED ((DRM_RESULT)0x800480D4L)

/*
 * MessageId: DRM_E_PKCRYPTO_FAILURE
 *
 * MessageText:
 *
 * An error occurred in an asymmetric cryptographic operation.
 *
 */
#define DRM_E_PKCRYPTO_FAILURE           ((DRM_RESULT)0x800480D5L)

/*
 * MessageId: DRM_E_INVALID_DST_SLOT_SIZE
 *
 * MessageText:
 *
 * Invalid DST slot size is specified.
 *
 */
#define DRM_E_INVALID_DST_SLOT_SIZE      ((DRM_RESULT)0x800480D6L)


/* ============================================================
**
** DRM utility results: error codes from 0x80049000-0x800490ff.
**
** ============================================================
*/

#define DRMUTIL_BASECODE       ((DRM_RESULT)0x80049000L)

/*
 * MessageId: DRM_E_UNSUPPORTED_VERSION
 *
 * MessageText:
 *
 *  DRM_E_UNSUPPORTED_VERSION
 *
 */
#define DRM_E_UNSUPPORTED_VERSION        ((DRM_RESULT)0x80049005L)

/*
 * MessageId: DRM_E_EXPIRED_CERT
 *
 * MessageText:
 *
 *  DRM_E_EXPIRED_CERT
 *
 */
#define DRM_E_EXPIRED_CERT               ((DRM_RESULT)0x80049006L)

/*
 * MessageId: DRM_E_DRMUTIL_INVALID_CERT
 *
 * MessageText:
 *
 *  DRM_E_DRMUTIL_INVALID_CERT
 *
 */
#define DRM_E_DRMUTIL_INVALID_CERT       ((DRM_RESULT)0x80049007L)


/* ============================================================
**
** PK specific errors (from 0x8004a000 to 0x8004afff)
**
** ============================================================
*/

/*
 * MessageId: DRM_E_DEVICE_NOT_REGISTERED
 *
 * MessageText:
 *
 * The DEVICEID does not exist in the device store
 *
 */
#define DRM_E_DEVICE_NOT_REGISTERED      ((DRM_RESULT)0x8004A000L)

/*
 * MessageId: DRM_E_TOO_MANY_INCLUSION_GUIDS
 *
 * MessageText:
 *
 * The license contained more than DRM_MAX_INCLUSION_GUIDS entries in its inclusion list
 *
 */
#define DRM_E_TOO_MANY_INCLUSION_GUIDS   ((DRM_RESULT)0x8004A001L)

/*
 * MessageId: DRM_E_REVOCATION_GUID_NOT_RECOGNIZED
 *
 * MessageText:
 *
 * The revocation list type GUID was not recognized
 *
 */
#define DRM_E_REVOCATION_GUID_NOT_RECOGNIZED ((DRM_RESULT)0x8004A002L)

/*
 * MessageId: DRM_E_LIC_CHAIN_TOO_DEEP
 *
 * MessageText:
 *
 * The license chained deeper than this implementation can handle
 *
 */
#define DRM_E_LIC_CHAIN_TOO_DEEP         ((DRM_RESULT)0x8004A003L)

/*
 * MessageId: DRM_E_DEVICE_SECURITY_LEVEL_TOO_LOW
 *
 * MessageText:
 *
 * The security level of the remote device is too low to receive the license
 *
 */
#define DRM_E_DEVICE_SECURITY_LEVEL_TOO_LOW ((DRM_RESULT)0x8004A004L)

/*
 * MessageId: DRM_E_DST_BLOCK_CACHE_CORRUPT
 *
 * MessageText:
 *
 * The block header cache returned invalid data
 *
 */
#define DRM_E_DST_BLOCK_CACHE_CORRUPT    ((DRM_RESULT)0x8004A005L)

/*
 * MessageId: DRM_E_DST_BLOCK_CACHE_MISS
 *
 * MessageText:
 *
 * The block header cache didn't contain the requested block header
 *
 */
#define DRM_E_DST_BLOCK_CACHE_MISS       ((DRM_RESULT)0x8004A007L)

/*
 * MessageId: DRM_E_INVALID_METERRESPONSE_SIGNATURE
 *
 * MessageText:
 *
 * Invalid signature in meter response
 *
 */
#define DRM_E_INVALID_METERRESPONSE_SIGNATURE ((DRM_RESULT)0x8004A013L)

/*
 * MessageId: DRM_E_INVALID_LICENSE_REVOCATION_LIST_SIGNATURE
 *
 * MessageText:
 *
 * Invalid signature in license revocation list.
 *
 */
#define DRM_E_INVALID_LICENSE_REVOCATION_LIST_SIGNATURE ((DRM_RESULT)0x8004A014L)

/*
 * MessageId: DRM_E_INVALID_METERCERT_SIGNATURE
 *
 * MessageText:
 *
 * Invalid signature in metering certificate
 *
 */
#define DRM_E_INVALID_METERCERT_SIGNATURE ((DRM_RESULT)0x8004A015L)

/*
 * MessageId: DRM_E_METERSTORE_DATA_NOT_FOUND
 *
 * MessageText:
 *
 * Metering data slot not found due to bad data in response file
 *
 */
#define DRM_E_METERSTORE_DATA_NOT_FOUND  ((DRM_RESULT)0x8004A016L)

/*
 * MessageId: DRM_E_INVALID_REVOCATION_LIST
 *
 * MessageText:
 *
 * The revocation list version does not match the current revocation version
 *
 */
#define DRM_E_INVALID_REVOCATION_LIST    ((DRM_RESULT)0x8004A018L)

/*
 * MessageId: DRM_E_ENVELOPE_CORRUPT
 *
 * MessageText:
 *
 * The envelope archive or file is corrupt
 *
 */
#define DRM_E_ENVELOPE_CORRUPT           ((DRM_RESULT)0x8004A019L)

/*
 * MessageId: DRM_E_ENVELOPE_FILE_NOT_COMPATIBLE
 *
 * MessageText:
 *
 * The envelope file is not compatible with this version of the porting kit
 *
 */
#define DRM_E_ENVELOPE_FILE_NOT_COMPATIBLE ((DRM_RESULT)0x8004A01AL)

/*
 * MessageId: DRM_E_EXTENDED_RESTRICTION_NOT_UNDERSTOOD
 *
 * MessageText:
 *
 * An extensible restriction was not understood by the app, and is mark as being required
 *
 */
#define DRM_E_EXTENDED_RESTRICTION_NOT_UNDERSTOOD ((DRM_RESULT)0x8004A01BL)

/*
 * MessageId: DRM_E_INVALID_SLK
 *
 * MessageText:
 *
 * An ILA SLK (symmetric session key) was found, but did not contain valid data
 *
 */
#define DRM_E_INVALID_SLK                ((DRM_RESULT)0x8004A01CL)

/*
 * MessageId: DRM_E_DEVCERT_MODEL_MISMATCH
 *
 * MessageText:
 *
 * The model string in the certificate does not match the model of the device and so the cert must be re-generated.
 *
 */
#define DRM_E_DEVCERT_MODEL_MISMATCH     ((DRM_RESULT)0x8004A01DL)

/*
 * MessageId: DRM_E_OUTDATED_REVOCATION_LIST
 *
 * MessageText:
 *
 * The revocation list is outdated. It is required for the revocation list to be refreshed at least every 90 days.
 *
 */
#define DRM_E_OUTDATED_REVOCATION_LIST   ((DRM_RESULT)0x8004A01EL)


/* ============================================================
**
** Drm Core errors (from 0x8004c000 to 0x8004dfff)
**
** ============================================================
*/

/*
 * MessageId: DRM_E_DEVICE_NOT_INITIALIZED
 *
 * MessageText:
 *
 * This device has not been initialized against a DRM init service
 *
 */
#define DRM_E_DEVICE_NOT_INITIALIZED     ((DRM_RESULT)0x8004C001L)

/*
 * MessageId: DRM_E_DRM_NOT_INITIALIZED
 *
 * MessageText:
 *
 * The app has not call DRM_Init properly
 *
 */
#define DRM_E_DRM_NOT_INITIALIZED        ((DRM_RESULT)0x8004C002L)

/*
 * MessageId: DRM_E_INVALID_RIGHT
 *
 * MessageText:
 *
 * A right in the license in invalid
 *
 */
#define DRM_E_INVALID_RIGHT              ((DRM_RESULT)0x8004C003L)

/*
 * MessageId: DRM_E_INVALID_LICENSE
 *
 * MessageText:
 *
 * The license is invalid
 *
 */
#define DRM_E_INVALID_LICENSE            ((DRM_RESULT)0x8004C006L)

/*
 * MessageId: DRM_E_CONDITION_NOT_SUPPORTED
 *
 * MessageText:
 *
 * A condition in the license is not supported by this verison of DRM
 *
 */
#define DRM_E_CONDITION_NOT_SUPPORTED    ((DRM_RESULT)0x8004C008L)

/*
 * MessageId: DRM_E_LICENSE_EXPIRED
 *
 * MessageText:
 *
 * The license has expired either by depleting a play count or via an end time.
 *
 */
#define DRM_E_LICENSE_EXPIRED            ((DRM_RESULT)0x8004C009L)

/*
 * MessageId: DRM_E_RIGHTS_NOT_AVAILABLE
 *
 * MessageText:
 *
 * The rights the app has requested are not available in the license
 *
 */
#define DRM_E_RIGHTS_NOT_AVAILABLE       ((DRM_RESULT)0x8004C00BL)

/*
 * MessageId: DRM_E_LICENSE_MISMATCH
 *
 * MessageText:
 *
 * The license content id/ sku id doesn't match that requested by the app
 *
 */
#define DRM_E_LICENSE_MISMATCH           ((DRM_RESULT)0x8004C00CL)

/*
 * MessageId: DRM_E_WRONG_TOKEN_TYPE
 *
 * MessageText:
 *
 * The token parameter was of an incompatible type.
 *
 */
#define DRM_E_WRONG_TOKEN_TYPE           ((DRM_RESULT)0x8004C00DL)

/*
 * MessageId: DRM_E_LICENSE_NOT_BOUND
 *
 * MessageText:
 *
 * A license has not been bound to. Decrypt can not happen without a successful bind call
 *
 */
#define DRM_E_LICENSE_NOT_BOUND          ((DRM_RESULT)0x8004C00FL)

/*
 * MessageId: DRM_E_HASH_MISMATCH
 *
 * MessageText:
 *
 * A Keyed Hash check failed.
 *
 */
#define DRM_E_HASH_MISMATCH              ((DRM_RESULT)0x8004C010L)

/*
 * MessageId: DRM_E_LICENSESTORE_NOT_FOUND
 *
 * MessageText:
 *
 * The external license store was not found.
 *
 */
#define DRM_E_LICENSESTORE_NOT_FOUND     ((DRM_RESULT)0x8004C012L)

/*
 * MessageId: DRM_E_LICENSE_NOT_FOUND
 *
 * MessageText:
 *
 * A license was not found in the license store.
 *
 */
#define DRM_E_LICENSE_NOT_FOUND          ((DRM_RESULT)0x8004C013L)

/*
 * MessageId: DRM_E_LICENSE_VERSION_NOT_SUPPORTED
 *
 * MessageText:
 *
 * The DRM license version is not supported by the DRM version on the device.
 *
 */
#define DRM_E_LICENSE_VERSION_NOT_SUPPORTED ((DRM_RESULT)0x8004C014L)

/*
 * MessageId: DRM_E_UNSUPPORTED_ALGORITHM
 *
 * MessageText:
 *
 * The encryption algorithm required for this operation is not supported.
 *
 */
#define DRM_E_UNSUPPORTED_ALGORITHM      ((DRM_RESULT)0x8004C016L)

/*
 * MessageId: DRM_E_INVALID_LICENSE_STORE
 *
 * MessageText:
 *
 * The license store version number is incorrect, or the store is invalid in some other way.
 *
 */
#define DRM_E_INVALID_LICENSE_STORE      ((DRM_RESULT)0x8004C019L)

/*
 * MessageId: DRM_E_FILE_READ_ERROR
 *
 * MessageText:
 *
 * There was an error reading a file.
 *
 */
#define DRM_E_FILE_READ_ERROR            ((DRM_RESULT)0x8004C01AL)

/*
 * MessageId: DRM_E_FILE_WRITE_ERROR
 *
 * MessageText:
 *
 * There was an error writing a file.
 *
 */
#define DRM_E_FILE_WRITE_ERROR           ((DRM_RESULT)0x8004C01BL)

/*
 * MessageId: DRM_E_DST_STORE_FULL
 *
 * MessageText:
 *
 * The data store is full.
 *
 */
#define DRM_E_DST_STORE_FULL             ((DRM_RESULT)0x8004C01DL)

/*
 * MessageId: DRM_E_NO_XML_OPEN_TAG
 *
 * MessageText:
 *
 * XML open tag not found
 *
 */
#define DRM_E_NO_XML_OPEN_TAG            ((DRM_RESULT)0x8004C01EL)

/*
 * MessageId: DRM_E_NO_XML_CLOSE_TAG
 *
 * MessageText:
 *
 * XML close tag not found
 *
 */
#define DRM_E_NO_XML_CLOSE_TAG           ((DRM_RESULT)0x8004C01FL)

/*
 * MessageId: DRM_E_INVALID_XML_TAG
 *
 * MessageText:
 *
 * Invalid XML tag
 *
 */
#define DRM_E_INVALID_XML_TAG            ((DRM_RESULT)0x8004C020L)

/*
 * MessageId: DRM_E_NO_XML_CDATA
 *
 * MessageText:
 *
 * No XML CDATA found
 *
 */
#define DRM_E_NO_XML_CDATA               ((DRM_RESULT)0x8004C021L)

/*
 * MessageId: DRM_E_DST_NAMESPACE_NOT_FOUND
 *
 * MessageText:
 *
 * No DST Namespace found
 *
 */
#define DRM_E_DST_NAMESPACE_NOT_FOUND    ((DRM_RESULT)0x8004C023L)

/*
 * MessageId: DRM_E_DST_SLOT_NOT_FOUND
 *
 * MessageText:
 *
 * DST Dataslot not found
 *
 */
#define DRM_E_DST_SLOT_NOT_FOUND         ((DRM_RESULT)0x8004C024L)

/*
 * MessageId: DRM_E_DST_SLOT_EXISTS
 *
 * MessageText:
 *
 * DST Dataslot already exists
 *
 */
#define DRM_E_DST_SLOT_EXISTS            ((DRM_RESULT)0x8004C025L)

/*
 * MessageId: DRM_E_DST_CORRUPTED
 *
 * MessageText:
 *
 * The data store is corrupted
 *
 */
#define DRM_E_DST_CORRUPTED              ((DRM_RESULT)0x8004C026L)

/*
 * MessageId: DRM_E_DST_SEEK_ERROR
 *
 * MessageText:
 *
 * There was an error attempting to seek in the Data Store
 *
 */
#define DRM_E_DST_SEEK_ERROR             ((DRM_RESULT)0x8004C027L)

/*
 * MessageId: DRM_E_INVALID_SECURESTORE_PASSWORD
 *
 * MessageText:
 *
 * The password used to open the secure store key was not able to validate the secure store hash.
 *
 */
#define DRM_E_INVALID_SECURESTORE_PASSWORD ((DRM_RESULT)0x8004C029L)

/*
 * MessageId: DRM_E_SECURESTORE_CORRUPT
 *
 * MessageText:
 *
 * The secure store is corrupt
 *
 */
#define DRM_E_SECURESTORE_CORRUPT        ((DRM_RESULT)0x8004C02AL)

/*
 * MessageId: DRM_E_SECURESTORE_FULL
 *
 * MessageText:
 *
 * The current secure store key is full. No more data can be added.
 *
 */
#define DRM_E_SECURESTORE_FULL           ((DRM_RESULT)0x8004C02BL)

/*
 * MessageId: DRM_E_DUPLICATED_HEADER_ATTRIBUTE
 *
 * MessageText:
 *
 * Duplicated attribute in Header
 *
 */
#define DRM_E_DUPLICATED_HEADER_ATTRIBUTE ((DRM_RESULT)0x8004C02DL)

/*
 * MessageId: DRM_E_NO_KID_IN_HEADER
 *
 * MessageText:
 *
 * No KID attribute in Header
 *
 */
#define DRM_E_NO_KID_IN_HEADER           ((DRM_RESULT)0x8004C02EL)

/*
 * MessageId: DRM_E_NO_LAINFO_IN_HEADER
 *
 * MessageText:
 *
 * No LAINFO attribute in Header
 *
 */
#define DRM_E_NO_LAINFO_IN_HEADER        ((DRM_RESULT)0x8004C02FL)

/*
 * MessageId: DRM_E_NO_CHECKSUM_IN_HEADER
 *
 * MessageText:
 *
 * No Checksum attribute in Header
 *
 */
#define DRM_E_NO_CHECKSUM_IN_HEADER      ((DRM_RESULT)0x8004C030L)

/*
 * MessageId: DRM_E_DST_BLOCK_MISMATCH
 *
 * MessageText:
 *
 * DST block mismatch
 *
 */
#define DRM_E_DST_BLOCK_MISMATCH         ((DRM_RESULT)0x8004C031L)

/*
 * MessageId: DRM_E_LICENSE_TOO_LONG
 *
 * MessageText:
 *
 * License size is too long
 *
 */
#define DRM_E_LICENSE_TOO_LONG           ((DRM_RESULT)0x8004C033L)

/*
 * MessageId: DRM_E_DST_EXISTS
 *
 * MessageText:
 *
 * A DST already exists in the specified location
 *
 */
#define DRM_E_DST_EXISTS                 ((DRM_RESULT)0x8004C034L)

/*
 * MessageId: DRM_E_INVALID_DEVICE_CERTIFICATE
 *
 * MessageText:
 *
 * The device certificate is invalid.
 *
 */
#define DRM_E_INVALID_DEVICE_CERTIFICATE ((DRM_RESULT)0x8004C035L)

/*
 * MessageId: DRM_E_DST_LOCK_FAILED
 *
 * MessageText:
 *
 * Locking a segment of the DST failed.
 *
 */
#define DRM_E_DST_LOCK_FAILED            ((DRM_RESULT)0x8004C036L)

/*
 * MessageId: DRM_E_FILE_SEEK_ERROR
 *
 * MessageText:
 *
 * File Seek Error
 *
 */
#define DRM_E_FILE_SEEK_ERROR            ((DRM_RESULT)0x8004C037L)

/*
 * MessageId: DRM_E_DST_NOT_LOCKED_EXCLUSIVE
 *
 * MessageText:
 *
 * Existing lock is not exclusive
 *
 */
#define DRM_E_DST_NOT_LOCKED_EXCLUSIVE   ((DRM_RESULT)0x8004C038L)

/*
 * MessageId: DRM_E_DST_EXCLUSIVE_LOCK_ONLY
 *
 * MessageText:
 *
 * Only exclusive lock is accepted
 *
 */
#define DRM_E_DST_EXCLUSIVE_LOCK_ONLY    ((DRM_RESULT)0x8004C039L)

/*
 * MessageId: DRM_E_V1_NOT_SUPPORTED
 *
 * MessageText:
 *
 * V1 Lic Acquisition is not supported
 *
 */
#define DRM_E_V1_NOT_SUPPORTED           ((DRM_RESULT)0x8004C03BL)

/*
 * MessageId: DRM_E_HEADER_NOT_SET
 *
 * MessageText:
 *
 * Content header is not set
 *
 */
#define DRM_E_HEADER_NOT_SET             ((DRM_RESULT)0x8004C03CL)

/*
 * MessageId: DRM_E_NEED_DEVCERT_INDIV
 *
 * MessageText:
 *
 * The device certificate is template. It need Devcert Indiv
 *
 */
#define DRM_E_NEED_DEVCERT_INDIV         ((DRM_RESULT)0x8004C03DL)

/*
 * MessageId: DRM_E_MACHINE_ID_MISMATCH
 *
 * MessageText:
 *
 * The device has Machine Id different from that in devcert.
 *
 */
#define DRM_E_MACHINE_ID_MISMATCH        ((DRM_RESULT)0x8004C03EL)

/*
 * MessageId: DRM_E_CLK_INVALID_RESPONSE
 *
 * MessageText:
 *
 * The secure clock response is invalid.
 *
 */
#define DRM_E_CLK_INVALID_RESPONSE       ((DRM_RESULT)0x8004C03FL)

/*
 * MessageId: DRM_E_CLK_INVALID_DATE
 *
 * MessageText:
 *
 * The secure clock response is invalid.
 *
 */
#define DRM_E_CLK_INVALID_DATE           ((DRM_RESULT)0x8004C040L)

/*
 * MessageId: DRM_E_INVALID_DEVCERT_TEMPLATE
 *
 * MessageText:
 *
 * The device certificate template is invalid.
 *
 */
#define DRM_E_INVALID_DEVCERT_TEMPLATE   ((DRM_RESULT)0x8004C042L)

/*
 * MessageId: DRM_E_DEVCERT_EXCEEDS_SIZE_LIMIT
 *
 * MessageText:
 *
 * The device certificate exceeds max size
 *
 */
#define DRM_E_DEVCERT_EXCEEDS_SIZE_LIMIT ((DRM_RESULT)0x8004C043L)

/*
 * MessageId: DRM_E_DEVCERT_READ_ERROR
 *
 * MessageText:
 *
 * Can't get the device certificate
 *
 */
#define DRM_E_DEVCERT_READ_ERROR         ((DRM_RESULT)0x8004C045L)

/*
 * MessageId: DRM_E_PRIVKEY_READ_ERROR
 *
 * MessageText:
 *
 * Can't get device private key
 *
 */
#define DRM_E_PRIVKEY_READ_ERROR         ((DRM_RESULT)0x8004C047L)

/*
 * MessageId: DRM_E_DEVCERT_TEMPLATE_READ_ERROR
 *
 * MessageText:
 *
 * Can't get the device certificate template
 *
 */
#define DRM_E_DEVCERT_TEMPLATE_READ_ERROR ((DRM_RESULT)0x8004C049L)

/*
 * MessageId: DRM_E_CLK_NOT_SUPPORTED
 *
 * MessageText:
 *
 * The secure clock is not supported.
 *
 */
#define DRM_E_CLK_NOT_SUPPORTED          ((DRM_RESULT)0x8004C04AL)

/*
 * MessageId: DRM_E_METERING_NOT_SUPPORTED
 *
 * MessageText:
 *
 * The Metering is not supported.
 *
 */
#define DRM_E_METERING_NOT_SUPPORTED     ((DRM_RESULT)0x8004C04CL)

/*
 * MessageId: DRM_E_CLK_RESET_STATE_READ_ERROR
 *
 * MessageText:
 *
 * Can not read Secure clock Reset State.
 *
 */
#define DRM_E_CLK_RESET_STATE_READ_ERROR ((DRM_RESULT)0x8004C04DL)

/*
 * MessageId: DRM_E_CLK_RESET_STATE_WRITE_ERROR
 *
 * MessageText:
 *
 * Can not write Secure clock Reset State.
 *
 */
#define DRM_E_CLK_RESET_STATE_WRITE_ERROR ((DRM_RESULT)0x8004C04EL)

/*
 * MessageId: DRM_E_XMLNOTFOUND
 *
 * MessageText:
 *
 * a required XML tag was not found
 *
 */
#define DRM_E_XMLNOTFOUND                ((DRM_RESULT)0x8004C04FL)

/*
 * MessageId: DRM_E_METERING_WRONG_TID
 *
 * MessageText:
 *
 * wrong TID sent on metering response
 *
 */
#define DRM_E_METERING_WRONG_TID         ((DRM_RESULT)0x8004C050L)

/*
 * MessageId: DRM_E_METERING_INVALID_COMMAND
 *
 * MessageText:
 *
 * wrong command sent on metering response
 *
 */
#define DRM_E_METERING_INVALID_COMMAND   ((DRM_RESULT)0x8004C051L)

/*
 * MessageId: DRM_E_METERING_STORE_CORRUPT
 *
 * MessageText:
 *
 * The metering store is corrupt
 *
 */
#define DRM_E_METERING_STORE_CORRUPT     ((DRM_RESULT)0x8004C052L)

/*
 * MessageId: DRM_E_CERTIFICATE_REVOKED
 *
 * MessageText:
 *
 * A certificate given to DRM was revoked.
 *
 */
#define DRM_E_CERTIFICATE_REVOKED        ((DRM_RESULT)0x8004C053L)

/*
 * MessageId: DRM_E_CRYPTO_FAILED
 *
 * MessageText:
 *
 * A cryptographic operation failed.
 *
 */
#define DRM_E_CRYPTO_FAILED              ((DRM_RESULT)0x8004C054L)

/*
 * MessageId: DRM_E_STACK_CORRUPT
 *
 * MessageText:
 *
 * The stack allocator context is corrupt. Likely a buffer overrun problem.
 *
 */
#define DRM_E_STACK_CORRUPT              ((DRM_RESULT)0x8004C055L)

/*
 * MessageId: DRM_E_UNKNOWN_BINDING_KEY
 *
 * MessageText:
 *
 * A matching binding key could not be found for the license.
 *
 */
#define DRM_E_UNKNOWN_BINDING_KEY        ((DRM_RESULT)0x8004C056L)

/*
 * MessageId: DRM_E_V1_LICENSE_CHAIN_NOT_SUPPORTED
 *
 * MessageText:
 *
 * License chaining with V1 content is not supported.
 *
 */
#define DRM_E_V1_LICENSE_CHAIN_NOT_SUPPORTED ((DRM_RESULT)0x8004C057L)

/*
 * MessageId: DRM_E_POLICY_METERING_DISABLED
 *
 * MessageText:
 *
 * Metering code was called but metering is disabled by group or user policy
 *
 */
#define DRM_E_POLICY_METERING_DISABLED   ((DRM_RESULT)0x8004C059L)

/*
 * MessageId: DRM_E_CLK_NOT_SET
 *
 * MessageText:
 *
 * Time based licenses can not be used because the secure clock is not set on the device.
 *
 */
#define DRM_E_CLK_NOT_SET                ((DRM_RESULT)0x8004C05BL)

/*
 * MessageId: DRM_E_NO_CLK_SUPPORTED
 *
 * MessageText:
 *
 * Time based licenses can not be used because the device does not support any clock.
 *
 */
#define DRM_E_NO_CLK_SUPPORTED           ((DRM_RESULT)0x8004C05CL)

/*
 * MessageId: DRM_E_NO_URL
 *
 * MessageText:
 *
 * Can not find URL info.
 *
 */
#define DRM_E_NO_URL                     ((DRM_RESULT)0x8004C05DL)

/*
 * MessageId: DRM_E_UNKNOWN_DEVICE_PROPERTY
 *
 * MessageText:
 *
 * Unknown device property.
 *
 */
#define DRM_E_UNKNOWN_DEVICE_PROPERTY    ((DRM_RESULT)0x8004C05EL)

/*
 * MessageId: DRM_E_METERING_MID_MISMATCH
 *
 * MessageText:
 *
 * The metering ID is not same in Metering Cert and metering response data
 *
 */
#define DRM_E_METERING_MID_MISMATCH      ((DRM_RESULT)0x8004C05FL)

/*
 * MessageId: DRM_E_METERING_RESPONSE_DECRYPT_FAILED
 *
 * MessageText:
 *
 * The encrypted section of metering response can not be decrypted
 *
 */
#define DRM_E_METERING_RESPONSE_DECRYPT_FAILED ((DRM_RESULT)0x8004C060L)

/*
 * MessageId: DRM_E_RIV_TOO_SMALL
 *
 * MessageText:
 *
 * RIV on the machine is too small.
 *
 */
#define DRM_E_RIV_TOO_SMALL              ((DRM_RESULT)0x8004C063L)

/*
 * MessageId: DRM_E_STACK_ALREADY_INITIALIZED
 *
 * MessageText:
 *
 * DRM_STK_Init called for initialized stack
 *
 */
#define DRM_E_STACK_ALREADY_INITIALIZED  ((DRM_RESULT)0x8004C064L)

/*
 * MessageId: DRM_E_DEVCERT_REVOKED
 *
 * MessageText:
 *
 * The device certificate given to DRM is revoked.
 *
 */
#define DRM_E_DEVCERT_REVOKED            ((DRM_RESULT)0x8004C065L)

/*
 * MessageId: DRM_E_OEM_RSA_DECRYPTION_ERROR
 *
 * MessageText:
 *
 * Error in OEM RSA Decryption.
 *
 */
#define DRM_E_OEM_RSA_DECRYPTION_ERROR   ((DRM_RESULT)0x8004C066L)

/*
 * MessageId: DRM_E_INVALID_DEVSTORE_ATTRIBUTE
 *
 * MessageText:
 *
 * Invalid device attributes in the device store
 *
 */
#define DRM_E_INVALID_DEVSTORE_ATTRIBUTE ((DRM_RESULT)0x8004C067L)

/*
 * MessageId: DRM_E_INVALID_DEVSTORE_ENTRY
 *
 * MessageText:
 *
 * The device store data entry is corrupted
 *
 */
#define DRM_E_INVALID_DEVSTORE_ENTRY     ((DRM_RESULT)0x8004C068L)

/*
 * MessageId: DRM_E_OEM_RSA_ENCRYPTION_ERROR
 *
 * MessageText:
 *
 * Error in OEM RSA Encryption process
 *
 */
#define DRM_E_OEM_RSA_ENCRYPTION_ERROR   ((DRM_RESULT)0x8004C069L)

/*
 * MessageId: DRM_E_DST_NAMESPACE_EXISTS
 *
 * MessageText:
 *
 * The DST Namespace already exists.
 *
 */
#define DRM_E_DST_NAMESPACE_EXISTS       ((DRM_RESULT)0x8004C06AL)

/*
 * MessageId: DRM_E_PERF_SCOPING_ERROR
 *
 * MessageText:
 *
 * Error in performance scope context
 *
 */
#define DRM_E_PERF_SCOPING_ERROR         ((DRM_RESULT)0x8004C06BL)

/*
 * MessageId: DRM_E_OEM_RSA_INVALID_PRIVATE_KEY
 *
 * MessageText:
 *
 * Invalid private key.
 *
 */
#define DRM_E_OEM_RSA_INVALID_PRIVATE_KEY ((DRM_RESULT)0x8004C06DL)

/*
 * MessageId: DRM_E_NO_OPL_CALLBACK
 *
 * MessageText:
 *
 * There is no callback function to process the output restrictions specified in the license
 *
 */
#define DRM_E_NO_OPL_CALLBACK            ((DRM_RESULT)0x8004C06EL)

/*
 * MessageId: DRM_E_INVALID_PLAYREADY_OBJECT
 *
 * MessageText:
 *
 * Structure of PlayReady object is invalid
 *
 */
#define DRM_E_INVALID_PLAYREADY_OBJECT   ((DRM_RESULT)0x8004C06FL)

/*
 * MessageId: DRM_E_DUPLICATE_LICENSE
 *
 * MessageText:
 *
 * There is already a license in the store with the same KID & LID
 *
 */
#define DRM_E_DUPLICATE_LICENSE          ((DRM_RESULT)0x8004C070L)

/*
 * MessageId: DRM_E_RECORD_NOT_FOUND
 *
 * MessageText:
 *
 * Record with requested type was not found in PlayReady object.
 *
 */
#define DRM_E_RECORD_NOT_FOUND           ((DRM_RESULT)0x8004C072L)

/*
 * MessageId: DRM_E_BUFFER_BOUNDS_EXCEEDED
 *
 * MessageText:
 *
 * An array is being referenced outside of it's bounds.
 *
 */
#define DRM_E_BUFFER_BOUNDS_EXCEEDED     ((DRM_RESULT)0x8004C073L)

/*
 * MessageId: DRM_E_INVALID_BASE64
 *
 * MessageText:
 *
 * An input string contains invalid Base64 characters.
 *
 */
#define DRM_E_INVALID_BASE64             ((DRM_RESULT)0x8004C074L)

/*
 * MessageId: DRM_E_PROTOCOL_VERSION_NOT_SUPPORTED
 *
 * MessageText:
 *
 * The protocol version is not supported.
 *
 */
#define DRM_E_PROTOCOL_VERSION_NOT_SUPPORTED ((DRM_RESULT)0x8004C075L)

/*
 * MessageId: DRM_E_INVALID_LICENSE_RESPONSE_SIGNATURE
 *
 * MessageText:
 *
 * Cannot verify license acquisition's response because signature is invalid.
 *
 */
#define DRM_E_INVALID_LICENSE_RESPONSE_SIGNATURE ((DRM_RESULT)0x8004C076L)

/*
 * MessageId: DRM_E_INVALID_LICENSE_RESPONSE_ID
 *
 * MessageText:
 *
 * Cannot verify license acquisition's response because response ID is invalid.
 *
 */
#define DRM_E_INVALID_LICENSE_RESPONSE_ID ((DRM_RESULT)0x8004C077L)

/*
 * MessageId: DRM_E_LICENSE_RESPONSE_SIGNATURE_MISSING
 *
 * MessageText:
 *
 * Cannot verify license acquisition's response because either response ID, license nonce or signature is missing.
 *
 */
#define DRM_E_LICENSE_RESPONSE_SIGNATURE_MISSING ((DRM_RESULT)0x8004C078L)

/*
 * MessageId: DRM_E_INVALID_DOMAIN_JOIN_RESPONSE_SIGNATURE
 *
 * MessageText:
 *
 * Cannot verify domain join response because signature is invalid.
 *
 */
#define DRM_E_INVALID_DOMAIN_JOIN_RESPONSE_SIGNATURE ((DRM_RESULT)0x8004C079L)

/*
 * MessageId: DRM_E_DOMAIN_JOIN_RESPONSE_SIGNATURE_MISSING
 *
 * MessageText:
 *
 * Cannot verify domain join response because either signing certificate chain or signature is missing.
 *
 */
#define DRM_E_DOMAIN_JOIN_RESPONSE_SIGNATURE_MISSING ((DRM_RESULT)0x8004C07AL)

/*
 * MessageId: DRM_E_ACTIVATION_REQUIRED
 *
 * MessageText:
 *
 * The device must be activated before initialization can succeed.
 *
 */
#define DRM_E_ACTIVATION_REQUIRED        ((DRM_RESULT)0x8004C07BL)

/*
 * MessageId: DRM_E_ACTIVATION_INTERNAL_ERROR
 *
 * MessageText:
 *
 * A server error occurred during device activation.
 *
 */
#define DRM_E_ACTIVATION_INTERNAL_ERROR  ((DRM_RESULT)0x8004C07CL)

/*
 * MessageId: DRM_E_ACTIVATION_GROUP_CERT_REVOKED_ERROR
 *
 * MessageText:
 *
 * The activation group cert has been revoked and the application must be updated with a new client lib.
 *
 */
#define DRM_E_ACTIVATION_GROUP_CERT_REVOKED_ERROR ((DRM_RESULT)0x8004C07DL)

/*
 * MessageId: DRM_E_ACTIVATION_NEW_CLIENT_LIB_REQUIRED_ERROR
 *
 * MessageText:
 *
 * The client lib used by the application is not supported and must be updated.
 *
 */
#define DRM_E_ACTIVATION_NEW_CLIENT_LIB_REQUIRED_ERROR ((DRM_RESULT)0x8004C07EL)

/*
 * MessageId: DRM_E_ACTIVATION_BAD_REQUEST
 *
 * MessageText:
 *
 * The activation request is invalid
 *
 */
#define DRM_E_ACTIVATION_BAD_REQUEST     ((DRM_RESULT)0x8004C07FL)

/*
 * MessageId: DRM_E_FILEIO_ERROR
 *
 * MessageText:
 *
 * Encountered a system error during file I/O.
 *
 */
#define DRM_E_FILEIO_ERROR               ((DRM_RESULT)0x8004C080L)

/*
 * MessageId: DRM_E_DISK_SPACE_ERROR
 *
 * MessageText:
 *
 * Out of disk space for storing playready files.
 *
 */
#define DRM_E_DISK_SPACE_ERROR           ((DRM_RESULT)0x8004C081L)

/*
 * MessageId: DRM_E_UPLINK_LICENSE_NOT_FOUND
 *
 * MessageText:
 *
 * A license was found in the license store but no license was found for its uplink ID.
 *
 */
#define DRM_E_UPLINK_LICENSE_NOT_FOUND   ((DRM_RESULT)0x8004C082L)

/*
 * MessageId: DRM_E_ACTIVATION_CLIENT_ALREADY_CURRENT
 *
 * MessageText:
 *
 * The activation client already has the lastest verion.
 *
 */
#define DRM_E_ACTIVATION_CLIENT_ALREADY_CURRENT ((DRM_RESULT)0x8004C083L)

/*
 * MessageId: DRM_E_LICENSE_REALTIME_EXPIRED
 *
 * MessageText:
 *
 * The license has expired during decryption due to the RealTimeExpiration Restriction.
 *
 */
#define DRM_E_LICENSE_REALTIME_EXPIRED   ((DRM_RESULT)0x8004C084L)


/* ------------------------------------------------------------
**
** License evaluator errors: error codes from DRM_E_BASECODE+0xC0 to
** DRM_E_BASECODE+0xDF, 0x8004c0c0-0x8004c0df.
**
** ------------------------------------------------------------
*/

#define DRM_E_LICEVAL_BASECODE                  DRM_E_BASECODE+0xC0

/*
 * MessageId: DRM_E_LICEVAL_LICENSE_NOT_SUPPLIED
 *
 * MessageText:
 *
 * License not supplied in the liceval context
 *
 */
#define DRM_E_LICEVAL_LICENSE_NOT_SUPPLIED ((DRM_RESULT)0x8004C0C0L)

/*
 * MessageId: DRM_E_LICEVAL_KID_MISMATCH
 *
 * MessageText:
 *
 * Mismatch between KID from header and the one inside license
 *
 */
#define DRM_E_LICEVAL_KID_MISMATCH       ((DRM_RESULT)0x8004C0C1L)

/*
 * MessageId: DRM_E_LICEVAL_LICENSE_REVOKED
 *
 * MessageText:
 *
 * License for this content has been revoked
 *
 */
#define DRM_E_LICEVAL_LICENSE_REVOKED    ((DRM_RESULT)0x8004C0C2L)

/*
 * MessageId: DRM_E_LICEVAL_UPDATE_FAILURE
 *
 * MessageText:
 *
 * Failed to update content revocation
 *
 */
#define DRM_E_LICEVAL_UPDATE_FAILURE     ((DRM_RESULT)0x8004C0C3L)

/*
 * MessageId: DRM_E_LICEVAL_REQUIRED_REVOCATION_LIST_NOT_AVAILABLE
 *
 * MessageText:
 *
 * Failed to update content revocation
 *
 */
#define DRM_E_LICEVAL_REQUIRED_REVOCATION_LIST_NOT_AVAILABLE ((DRM_RESULT)0x8004C0C4L)

/*
 * MessageId: DRM_E_LICEVAL_INVALID_PRND_LICENSE
 *
 * MessageText:
 *
 * License is an invalid PRND license. PRND license cannot have metering ID, expire-after-first-play or domain properties.
 *
 */
#define DRM_E_LICEVAL_INVALID_PRND_LICENSE ((DRM_RESULT)0x8004C0C5L)


/* ------------------------------------------------------------
**
** XMR parser and builder errors: error codes from DRM_E_BASECODE+0xE0 to
** DRM_E_BASECODE+0xFF, 0x8004c0e0-0x8004c0ff.
**
** ------------------------------------------------------------
*/

#define DRM_E_XMR_BASECODE                      DRM_E_BASECODE+0xE0

/*
 * MessageId: DRM_E_XMR_OBJECT_ALREADY_EXISTS
 *
 * MessageText:
 *
 * XMR builder context already has this object.
 *
 */
#define DRM_E_XMR_OBJECT_ALREADY_EXISTS  ((DRM_RESULT)0x8004C0E0L)

/*
 * MessageId: DRM_E_XMR_OBJECT_NOT_FOUND
 *
 * MessageText:
 *
 * XMR object was not found.
 *
 */
#define DRM_E_XMR_OBJECT_NOT_FOUND       ((DRM_RESULT)0x8004C0E1L)

/*
 * MessageId: DRM_E_XMR_REQUIRED_OBJECT_MISSING
 *
 * MessageText:
 *
 * XMR license doesn't have one or more required objects.
 *
 */
#define DRM_E_XMR_REQUIRED_OBJECT_MISSING ((DRM_RESULT)0x8004C0E2L)

/*
 * MessageId: DRM_E_XMR_INVALID_UNKNOWN_OBJECT
 *
 * MessageText:
 *
 * Invalid unknown object
 *
 */
#define DRM_E_XMR_INVALID_UNKNOWN_OBJECT ((DRM_RESULT)0x8004C0E3L)

/*
 * MessageId: DRM_E_XMR_LICENSE_BINDABLE
 *
 * MessageText:
 *
 * XMR license does not contain the Cannot Bind right
 *
 */
#define DRM_E_XMR_LICENSE_BINDABLE       ((DRM_RESULT)0x8004C0E4L)

/*
 * MessageId: DRM_E_XMR_LICENSE_NOT_BINDABLE
 *
 * MessageText:
 *
 * XMR license cannot be bound to because of the Cannot Bind right
 *
 */
#define DRM_E_XMR_LICENSE_NOT_BINDABLE   ((DRM_RESULT)0x8004C0E5L)

/*
 * MessageId: DRM_E_XMR_UNSUPPORTED_XMR_VERSION
 *
 * MessageText:
 *
 * The version of XMR license is not supported for the current action
 *
 */
#define DRM_E_XMR_UNSUPPORTED_XMR_VERSION ((DRM_RESULT)0x8004C0E6L)


/* ------------------------------------------------------------
**
** Device certificate errors: error codes from DRM_E_BASECODE+0x200 to
** DRM_E_BASECODE+0x4FF, 0x8004c200-0x8004c2ff.
**
** ------------------------------------------------------------
*/

#define DRM_E_CERT_BASECODE                  DRM_E_BASECODE+0x200

/*
 * MessageId: DRM_E_INVALID_DEVCERT_ATTRIBUTE
 *
 * MessageText:
 *
 * The attributes in the Device certificate are invalid
 *
 */
#define DRM_E_INVALID_DEVCERT_ATTRIBUTE  ((DRM_RESULT)0x8004C200L)


/* ------------------------------------------------------------
**
** Test errors: error codes from DRM_E_BASECODE+0x300 to
** DRM_E_BASECODE+0x3E7, 0x8004c300-0x8004c3e7.
**
** ------------------------------------------------------------
*/

#define DRM_E_TEST_BASECODE        DRM_E_BASECODE+0x300
#define DRM_S_TEST_BASECODE        DRM_S_BASECODE+0x300

/*
 * MessageId: DRM_S_TEST_SKIP_FILE
 *
 * MessageText:
 *
 * Skip processing this file, not an eror.
 *
 */
#define DRM_S_TEST_SKIP_FILE             ((DRM_RESULT)0x0004C300L)

/*
 * MessageId: DRM_S_TEST_CONVERTED_FILE
 *
 * MessageText:
 *
 * The file was converted to a PlayReady file during the action.
 *
 */
#define DRM_S_TEST_CONVERTED_FILE        ((DRM_RESULT)0x0004C301L)

/*
 * MessageId: DRM_E_TEST_PKCRYPTO_FAILURE
 *
 * MessageText:
 *
 * Error in PK encryption/decryption crypto test cases.
 *
 */
#define DRM_E_TEST_PKCRYPTO_FAILURE      ((DRM_RESULT)0x8004C300L)

/*
 * MessageId: DRM_E_TEST_PKSIGN_VERIFY_ERROR
 *
 * MessageText:
 *
 * Digital signature verification failed.
 *
 */
#define DRM_E_TEST_PKSIGN_VERIFY_ERROR   ((DRM_RESULT)0x8004C301L)

/*
 * MessageId: DRM_E_TEST_ENCRYPT_ERROR
 *
 * MessageText:
 *
 * Error in encryption of cipher text.
 *
 */
#define DRM_E_TEST_ENCRYPT_ERROR         ((DRM_RESULT)0x8004C302L)

/*
 * MessageId: DRM_E_TEST_RC4KEY_FAILED
 *
 * MessageText:
 *
 * RC4 key failed during crypto operations.
 *
 */
#define DRM_E_TEST_RC4KEY_FAILED         ((DRM_RESULT)0x8004C303L)

/*
 * MessageId: DRM_E_TEST_DECRYPT_ERROR
 *
 * MessageText:
 *
 * Error in cipher text decryption.
 *
 */
#define DRM_E_TEST_DECRYPT_ERROR         ((DRM_RESULT)0x8004C304L)

/*
 * MessageId: DRM_E_TEST_DESKEY_FAILED
 *
 * MessageText:
 *
 * Decrypted data not equal to original data in a DES operation.
 *
 */
#define DRM_E_TEST_DESKEY_FAILED         ((DRM_RESULT)0x8004C305L)

/*
 * MessageId: DRM_E_TEST_CBC_INVERSEMAC_FAILURE
 *
 * MessageText:
 *
 * Decrypted data not equal to original in Inverse MAC operation.
 *
 */
#define DRM_E_TEST_CBC_INVERSEMAC_FAILURE ((DRM_RESULT)0x8004C306L)

/*
 * MessageId: DRM_E_TEST_HMAC_FAILURE
 *
 * MessageText:
 *
 * Error in hashed data in HMAC operation.
 *
 */
#define DRM_E_TEST_HMAC_FAILURE          ((DRM_RESULT)0x8004C307L)

/*
 * MessageId: DRM_E_TEST_INVALIDARG
 *
 * MessageText:
 *
 * Error in the number of arguments or argument data in Test files.
 *
 */
#define DRM_E_TEST_INVALIDARG            ((DRM_RESULT)0x8004C308L)

/*
 * MessageId: DRM_E_TEST_DEVICE_PRIVATE_KEY_INCORRECTLY_STORED
 *
 * MessageText:
 *
 * DRMManager context should not contain the device private key.
 *
 */
#define DRM_E_TEST_DEVICE_PRIVATE_KEY_INCORRECTLY_STORED ((DRM_RESULT)0x8004C30AL)

/*
 * MessageId: DRM_E_TEST_DRMMANAGER_CONTEXT_NULL
 *
 * MessageText:
 *
 * DRMManager context is NULL.
 *
 */
#define DRM_E_TEST_DRMMANAGER_CONTEXT_NULL ((DRM_RESULT)0x8004C30BL)

/*
 * MessageId: DRM_E_TEST_UNEXPECTED_REVINFO_RESULT
 *
 * MessageText:
 *
 * Revocation cache result was not as expected.
 *
 */
#define DRM_E_TEST_UNEXPECTED_REVINFO_RESULT ((DRM_RESULT)0x8004C30CL)

/*
 * MessageId: DRM_E_TEST_RIV_MISMATCH
 *
 * MessageText:
 *
 * Revocation Info Version(RIV) mismatch.
 *
 */
#define DRM_E_TEST_RIV_MISMATCH          ((DRM_RESULT)0x8004C30DL)

/*
 * MessageId: DRM_E_TEST_URL_ERROR
 *
 * MessageText:
 *
 * There is an error in the URL from the challenge generated.
 *
 */
#define DRM_E_TEST_URL_ERROR             ((DRM_RESULT)0x8004C310L)

/*
 * MessageId: DRM_E_TEST_MID_MISMATCH
 *
 * MessageText:
 *
 * The MIDs returned from the DRM_MANAGER_CONTEXT does not match the test input.
 *
 */
#define DRM_E_TEST_MID_MISMATCH          ((DRM_RESULT)0x8004C311L)

/*
 * MessageId: DRM_E_TEST_METER_CERTIFICATE_MISMATCH
 *
 * MessageText:
 *
 * The input data does not match with the Metering certificate returned from the license.
 *
 */
#define DRM_E_TEST_METER_CERTIFICATE_MISMATCH ((DRM_RESULT)0x8004C312L)

/*
 * MessageId: DRM_E_TEST_LICENSE_STATE_MISMATCH
 *
 * MessageText:
 *
 * The input data and license state returned from the license do not match.
 *
 */
#define DRM_E_TEST_LICENSE_STATE_MISMATCH ((DRM_RESULT)0x8004C313L)

/*
 * MessageId: DRM_E_TEST_SOURCE_ID_MISMATCH
 *
 * MessageText:
 *
 * The input data and license state returned from the license do not match.
 *
 */
#define DRM_E_TEST_SOURCE_ID_MISMATCH    ((DRM_RESULT)0x8004C316L)

/*
 * MessageId: DRM_E_TEST_UNEXPECTED_LICENSE_COUNT
 *
 * MessageText:
 *
 * The input data and the number of license from the KID do not match.
 *
 */
#define DRM_E_TEST_UNEXPECTED_LICENSE_COUNT ((DRM_RESULT)0x8004C317L)

/*
 * MessageId: DRM_E_TEST_UNEXPECTED_DEVICE_PROPERTY
 *
 * MessageText:
 *
 * Unknown device property.
 *
 */
#define DRM_E_TEST_UNEXPECTED_DEVICE_PROPERTY ((DRM_RESULT)0x8004C318L)

/*
 * MessageId: DRM_E_TEST_DRMMANAGER_MISALIGNED_BYTES
 *
 * MessageText:
 *
 * Error due to misalignment of bytes.
 *
 */
#define DRM_E_TEST_DRMMANAGER_MISALIGNED_BYTES ((DRM_RESULT)0x8004C319L)

/*
 * MessageId: DRM_E_TEST_LICENSE_RESPONSE_ERROR
 *
 * MessageText:
 *
 * The license response callbacks did not provide the expected data.
 *
 */
#define DRM_E_TEST_LICENSE_RESPONSE_ERROR ((DRM_RESULT)0x8004C31AL)

/*
 * MessageId: DRM_E_TEST_OPL_MISMATCH
 *
 * MessageText:
 *
 * The minimum levels of the compressed/uncompressed Digital and Analog Video do not match the OPL.
 *
 */
#define DRM_E_TEST_OPL_MISMATCH          ((DRM_RESULT)0x8004C31BL)

/*
 * MessageId: DRM_E_TEST_INVALID_OPL_CALLBACK
 *
 * MessageText:
 *
 * The callback type supplied is not valid.
 *
 */
#define DRM_E_TEST_INVALID_OPL_CALLBACK  ((DRM_RESULT)0x8004C31CL)

/*
 * MessageId: DRM_E_TEST_INCOMPLETE
 *
 * MessageText:
 *
 * The test function failed to complete.
 *
 */
#define DRM_E_TEST_INCOMPLETE            ((DRM_RESULT)0x8004C31DL)

/*
 * MessageId: DRM_E_TEST_UNEXPECTED_OUTPUT
 *
 * MessageText:
 *
 * The output of the function being tested does not match the expected output.
 *
 */
#define DRM_E_TEST_UNEXPECTED_OUTPUT     ((DRM_RESULT)0x8004C31EL)

/*
 * MessageId: DRM_E_TEST_DLA_NO_CONTENT_HEADER
 *
 * MessageText:
 *
 * Content Header Information was not retrieved correctly in DLA Sync Tests.
 *
 */
#define DRM_E_TEST_DLA_NO_CONTENT_HEADER ((DRM_RESULT)0x8004C31FL)

/*
 * MessageId: DRM_E_TEST_DLA_CONTENT_HEADER_FOUND
 *
 * MessageText:
 *
 * Content Header Information was found when it should not have been in DLA Sync Tests.
 *
 */
#define DRM_E_TEST_DLA_CONTENT_HEADER_FOUND ((DRM_RESULT)0x8004C320L)

/*
 * MessageId: DRM_E_TEST_SYNC_LSD_INCORRECT
 *
 * MessageText:
 *
 * DRM_SNC_GetSyncStoreEntry returned incorrect License State Data.
 *
 */
#define DRM_E_TEST_SYNC_LSD_INCORRECT    ((DRM_RESULT)0x8004C321L)

/*
 * MessageId: DRM_E_TEST_TOO_SLOW
 *
 * MessageText:
 *
 * The performance test failed because DRM took longer than its maximum time.
 *
 */
#define DRM_E_TEST_TOO_SLOW              ((DRM_RESULT)0x8004C322L)

/*
 * MessageId: DRM_E_TEST_LICENSESTORE_NOT_OPEN
 *
 * MessageText:
 *
 * The License Store contexts in the App Manager context are not open.
 *
 */
#define DRM_E_TEST_LICENSESTORE_NOT_OPEN ((DRM_RESULT)0x8004C323L)

/*
 * MessageId: DRM_E_TEST_DEVICE_NOT_INITED
 *
 * MessageText:
 *
 * The device instance has not been initialized prior to use.
 *
 */
#define DRM_E_TEST_DEVICE_NOT_INITED     ((DRM_RESULT)0x8004C324L)

/*
 * MessageId: DRM_E_TEST_VARIABLE_NOT_SET
 *
 * MessageText:
 *
 * A global variable needed for test execution has not been set correctly.
 *
 */
#define DRM_E_TEST_VARIABLE_NOT_SET      ((DRM_RESULT)0x8004C325L)

/*
 * MessageId: DRM_E_TEST_NOMORE
 *
 * MessageText:
 *
 * The same as DRM_E_NOMORE, only explicitly used in test code.
 *
 */
#define DRM_E_TEST_NOMORE                ((DRM_RESULT)0x8004C326L)

/*
 * MessageId: DRM_E_TEST_FILE_LOAD_ERROR
 *
 * MessageText:
 *
 * There was an error loading a test data file.
 *
 */
#define DRM_E_TEST_FILE_LOAD_ERROR       ((DRM_RESULT)0x8004C327L)

/*
 * MessageId: DRM_E_TEST_LICENSE_ACQ_FAILED
 *
 * MessageText:
 *
 * The attempt to acquire a license failed.
 *
 */
#define DRM_E_TEST_LICENSE_ACQ_FAILED    ((DRM_RESULT)0x8004C328L)

/*
 * MessageId: DRM_E_TEST_UNSUPPORTED_FILE_FORMAT
 *
 * MessageText:
 *
 * A file format is being used which is not supported by the test function.
 *
 */
#define DRM_E_TEST_UNSUPPORTED_FILE_FORMAT ((DRM_RESULT)0x8004C329L)

/*
 * MessageId: DRM_E_TEST_PARSING_ERROR
 *
 * MessageText:
 *
 * There was an error parsing input parameter.
 *
 */
#define DRM_E_TEST_PARSING_ERROR         ((DRM_RESULT)0x8004C32AL)

/*
 * MessageId: DRM_E_TEST_NOTIMPL
 *
 * MessageText:
 *
 * The specified test API is not implemented.
 *
 */
#define DRM_E_TEST_NOTIMPL               ((DRM_RESULT)0x8004C32BL)

/*
 * MessageId: DRM_E_TEST_VARIABLE_NOTFOUND
 *
 * MessageText:
 *
 * The specified test varaible was not found in the shared variable table.
 *
 */
#define DRM_E_TEST_VARIABLE_NOTFOUND     ((DRM_RESULT)0x8004C32CL)

/*
 * MessageId: DRM_E_TEST_VARIABLE_LISTFULL
 *
 * MessageText:
 *
 * The shared test variable table is full.
 *
 */
#define DRM_E_TEST_VARIABLE_LISTFULL     ((DRM_RESULT)0x8004C32DL)

/*
 * MessageId: DRM_E_TEST_UNEXPECTED_CONTENT_PROPERTY
 *
 * MessageText:
 *
 * Unknown content property.
 *
 */
#define DRM_E_TEST_UNEXPECTED_CONTENT_PROPERTY ((DRM_RESULT)0x8004C32EL)

/*
 * MessageId: DRM_E_TEST_PRO_HEADER_NOT_SET
 *
 * MessageText:
 *
 * PlayReady Object Header not set.
 *
 */
#define DRM_E_TEST_PRO_HEADER_NOT_SET    ((DRM_RESULT)0x8004C32FL)

/*
 * MessageId: DRM_E_TEST_NON_PRO_HEADER_TYPE
 *
 * MessageText:
 *
 * Incompatible header - PlayReady Object Header expected.
 *
 */
#define DRM_E_TEST_NON_PRO_HEADER_TYPE   ((DRM_RESULT)0x8004C330L)

/*
 * MessageId: DRM_E_TEST_INVALID_DEVICE_WRAPPER
 *
 * MessageText:
 *
 * The Device Simulator Device Wrapper is not valid.
 *
 */
#define DRM_E_TEST_INVALID_DEVICE_WRAPPER ((DRM_RESULT)0x8004C331L)

/*
 * MessageId: DRM_E_TEST_INVALID_WMDM_WRAPPER
 *
 * MessageText:
 *
 * The Device Simulator WMDM Wrapper is not valid.
 *
 */
#define DRM_E_TEST_INVALID_WMDM_WRAPPER  ((DRM_RESULT)0x8004C332L)

/*
 * MessageId: DRM_E_TEST_INVALID_WPD_WRAPPER
 *
 * MessageText:
 *
 * The Device Simulator WPD Wrapper is not valid.
 *
 */
#define DRM_E_TEST_INVALID_WPD_WRAPPER   ((DRM_RESULT)0x8004C333L)

/*
 * MessageId: DRM_E_TEST_INVALID_FILE
 *
 * MessageText:
 *
 * The data file given was invalid.
 *
 */
#define DRM_E_TEST_INVALID_FILE          ((DRM_RESULT)0x8004C334L)

/*
 * MessageId: DRM_E_TEST_PROPERTY_NOT_FOUND
 *
 * MessageText:
 *
 * The object did not have the property which was queried.
 *
 */
#define DRM_E_TEST_PROPERTY_NOT_FOUND    ((DRM_RESULT)0x8004C335L)

/*
 * MessageId: DRM_E_TEST_METERING_DATA_INCORRECT
 *
 * MessageText:
 *
 * The metering data reported is incorrect.
 *
 */
#define DRM_E_TEST_METERING_DATA_INCORRECT ((DRM_RESULT)0x8004C336L)

/*
 * MessageId: DRM_E_TEST_FILE_ALREADY_OPEN
 *
 * MessageText:
 *
 * The handle variable for a test file is not NULL. This indicates that a file was opened and not closed properly.
 *
 */
#define DRM_E_TEST_FILE_ALREADY_OPEN     ((DRM_RESULT)0x8004C337L)

/*
 * MessageId: DRM_E_TEST_FILE_NOT_OPEN
 *
 * MessageText:
 *
 * The handle variable for a test file is NULL. This indicates that a file was not opened.
 *
 */
#define DRM_E_TEST_FILE_NOT_OPEN         ((DRM_RESULT)0x8004C338L)

/*
 * MessageId: DRM_E_TEST_PICT_COLUMN_TOO_WIDE
 *
 * MessageText:
 *
 * The PICT input file contains a column which is too wide for the test parser to handle.
 *
 */
#define DRM_E_TEST_PICT_COLUMN_TOO_WIDE  ((DRM_RESULT)0x8004C339L)

/*
 * MessageId: DRM_E_TEST_PICT_COLUMN_MISMATCH
 *
 * MessageText:
 *
 * The PICT input file contains a row which doesn't have the same number of columns as the header row.
 *
 */
#define DRM_E_TEST_PICT_COLUMN_MISMATCH  ((DRM_RESULT)0x8004C33AL)

/*
 * MessageId: DRM_E_TEST_TUX_TEST_SKIPPED
 *
 * MessageText:
 *
 * TUX cannot find the speficied test case in target dll. Test Skipped.
 *
 */
#define DRM_E_TEST_TUX_TEST_SKIPPED      ((DRM_RESULT)0x8004C33BL)

/*
 * MessageId: DRM_E_TEST_KEYFILE_VERIFICATION_FAILURE
 *
 * MessageText:
 *
 * Verification of the Keyfile context failed.
 *
 */
#define DRM_E_TEST_KEYFILE_VERIFICATION_FAILURE ((DRM_RESULT)0x8004C33CL)

/*
 * MessageId: DRM_E_TEST_DATA_VERIFICATION_FAILURE
 *
 * MessageText:
 *
 * Data does not match expected value and failed verification.
 *
 */
#define DRM_E_TEST_DATA_VERIFICATION_FAILURE ((DRM_RESULT)0x8004C33DL)

/*
 * MessageId: DRM_E_TEST_NET_FAIL
 *
 * MessageText:
 *
 * The Test failed to perform Network I/O.
 *
 */
#define DRM_E_TEST_NET_FAIL              ((DRM_RESULT)0x8004C33EL)

/*
 * MessageId: DRM_E_TEST_CLEANUP_FAIL
 *
 * MessageText:
 *
 * A failure occurred during the test case cleanup phase.
 *
 */
#define DRM_E_TEST_CLEANUP_FAIL          ((DRM_RESULT)0x8004C33FL)


/* ------------------------------------------------------------
**
** Errors of the range 0x8004c3e8-0x8004c3f8 (range is where
** *decimal* +1000 starts.
**
** ------------------------------------------------------------
*/

/*
 * MessageId: DRM_E_LOGICERR
 *
 * MessageText:
 *
 * DRM code has a logic error in it.  This result should never be returned.  There is an unhandled code path if it is returned.
 *
 */
#define DRM_E_LOGICERR                   ((DRM_RESULT)0x8004C3E8L)

/*
 * MessageId: DRM_E_INVALID_REV_INFO
 *
 * MessageText:
 *
 * The rev info blob is invalid.
 *
 */
#define DRM_E_INVALID_REV_INFO           ((DRM_RESULT)0x8004C3E9L)

/*
 * MessageId: DRM_E_SYNCLIST_NOT_SUPPORTED
 *
 * MessageText:
 *
 * The device does not support synclist.
 *
 */
#define DRM_E_SYNCLIST_NOT_SUPPORTED     ((DRM_RESULT)0x8004C3EAL)

/*
 * MessageId: DRM_E_REVOCATION_BUFFER_TOO_SMALL
 *
 * MessageText:
 *
 * The revocation buffer is too small.
 *
 */
#define DRM_E_REVOCATION_BUFFER_TOO_SMALL ((DRM_RESULT)0x8004C3EBL)

/*
 * MessageId: DRM_E_DEVICE_ALREADY_REGISTERED
 *
 * MessageText:
 *
 * There exists already a device in the device store with the same DEVICEID that was given.
 *
 */
#define DRM_E_DEVICE_ALREADY_REGISTERED  ((DRM_RESULT)0x8004C3ECL)

/*
 * MessageId: DRM_E_DST_NOT_COMPATIBLE
 *
 * MessageText:
 *
 * The data store version is incompatible with this version of DRM.
 *
 */
#define DRM_E_DST_NOT_COMPATIBLE         ((DRM_RESULT)0x8004C3EDL)

/*
 * MessageId: DRM_E_RSA_DECRYPTION_ERROR
 *
 * MessageText:
 *
 * The data block/Encoded message used in OAEP decoding is incorrect.
 *
 */
#define DRM_E_RSA_DECRYPTION_ERROR       ((DRM_RESULT)0x8004C3F0L)

/*
 * MessageId: DRM_E_OEM_RSA_MESSAGE_TOO_BIG
 *
 * MessageText:
 *
 * The base message buffer is larger than the given modulus.
 *
 */
#define DRM_E_OEM_RSA_MESSAGE_TOO_BIG    ((DRM_RESULT)0x8004C3F1L)

/*
 * MessageId: DRM_E_METERCERT_NOT_FOUND
 *
 * MessageText:
 *
 * The metering certificate was not found in the store.
 *
 */
#define DRM_E_METERCERT_NOT_FOUND        ((DRM_RESULT)0x8004C3F2L)

/*
 * MessageId: DRM_E_MODULAR_ARITHMETIC_FAILURE
 *
 * MessageText:
 *
 * A failure occurred in bignum modular arithmetic.
 *
 */
#define DRM_E_MODULAR_ARITHMETIC_FAILURE ((DRM_RESULT)0x8004C3F3L)

/*
 * MessageId: DRM_E_REVOCATION_INVALID_PACKAGE
 *
 * MessageText:
 *
 * The revocation package is invalid
 *
 */
#define DRM_E_REVOCATION_INVALID_PACKAGE ((DRM_RESULT)0x8004C3F5L)

/*
 * MessageId: DRM_E_HWID_ERROR
 *
 * MessageText:
 *
 * Failed to get the hardware ID.
 *
 */
#define DRM_E_HWID_ERROR                 ((DRM_RESULT)0x8004C3F6L)


/* ------------------------------------------------------------
**
** Domain errors: error codes from DRM_E_BASECODE+0x500 to
** DRM_E_BASECODE+0x57F, 0x8004c500-0x8004c57f.
**
** ------------------------------------------------------------
*/

#define DRM_E_DOMAIN_BASECODE       DRM_E_BASECODE + 0x500

/*
 * MessageId: DRM_E_DOMAIN_INVALID_GUID
 *
 * MessageText:
 *
 * Not a correct GUID.
 *
 */
#define DRM_E_DOMAIN_INVALID_GUID        ((DRM_RESULT)0x8004C500L)

/*
 * MessageId: DRM_E_DOMAIN_INVALID_CUSTOM_DATA_TYPE
 *
 * MessageText:
 *
 * Not a valid custom data type.
 *
 */
#define DRM_E_DOMAIN_INVALID_CUSTOM_DATA_TYPE ((DRM_RESULT)0x8004C501L)

/*
 * MessageId: DRM_E_DOMAIN_STORE_ADD_DATA
 *
 * MessageText:
 *
 * Failed to add data into the domain store.
 *
 */
#define DRM_E_DOMAIN_STORE_ADD_DATA      ((DRM_RESULT)0x8004C502L)

/*
 * MessageId: DRM_E_DOMAIN_STORE_GET_DATA
 *
 * MessageText:
 *
 * Failed to retrieve data from the domain store.
 *
 */
#define DRM_E_DOMAIN_STORE_GET_DATA      ((DRM_RESULT)0x8004C503L)

/*
 * MessageId: DRM_E_DOMAIN_STORE_DELETE_DATA
 *
 * MessageText:
 *
 * Failed to delete data from the domain store.
 *
 */
#define DRM_E_DOMAIN_STORE_DELETE_DATA   ((DRM_RESULT)0x8004C504L)

/*
 * MessageId: DRM_E_DOMAIN_STORE_OPEN_STORE
 *
 * MessageText:
 *
 * Failed to open the domain store.
 *
 */
#define DRM_E_DOMAIN_STORE_OPEN_STORE    ((DRM_RESULT)0x8004C505L)

/*
 * MessageId: DRM_E_DOMAIN_STORE_CLOSE_STORE
 *
 * MessageText:
 *
 * Failed to close the domain store.
 *
 */
#define DRM_E_DOMAIN_STORE_CLOSE_STORE   ((DRM_RESULT)0x8004C506L)

/*
 * MessageId: DRM_E_DOMAIN_BIND_LICENSE
 *
 * MessageText:
 *
 * Failed to bind to the domain license.
 *
 */
#define DRM_E_DOMAIN_BIND_LICENSE        ((DRM_RESULT)0x8004C507L)

/*
 * MessageId: DRM_E_DOMAIN_INVALID_CUSTOM_DATA
 *
 * MessageText:
 *
 * Not a valid custom data.
 *
 */
#define DRM_E_DOMAIN_INVALID_CUSTOM_DATA ((DRM_RESULT)0x8004C508L)

/*
 * MessageId: DRM_E_DOMAIN_NOT_FOUND
 *
 * MessageText:
 *
 * No domain information is found.
 *
 */
#define DRM_E_DOMAIN_NOT_FOUND           ((DRM_RESULT)0x8004C509L)

/*
 * MessageId: DRM_E_DOMAIN_INVALID_DOMKEYXMR_DATA
 *
 * MessageText:
 *
 * The domain join response contains invalid domain privkey XMR data.
 *
 */
#define DRM_E_DOMAIN_INVALID_DOMKEYXMR_DATA ((DRM_RESULT)0x8004C50AL)

/*
 * MessageId: DRM_E_DOMAIN_STORE_INVALID_KEY_RECORD
 *
 * MessageText:
 *
 * Invalid format of domain private key record read from the domain store.
 *
 */
#define DRM_E_DOMAIN_STORE_INVALID_KEY_RECORD ((DRM_RESULT)0x8004C50BL)


/* ------------------------------------------------------------
**
** PC errors returned by core logic: error codes from DRM_E_BASECODE+0x580 to
** DRM_E_BASECODE+0x5FF, 0x8004c580-0x8004c5ff.
**
** ------------------------------------------------------------
*/

#define DRM_E_PC_BASECODE           DRM_E_BASECODE + 0x580

/*
 * MessageId: DRM_E_DEVICE_DOMAIN_JOIN_REQUIRED
 *
 * MessageText:
 *
 * This error code communicates to the application that the device is not a member of a domain. The app can uses this error code in turn to decide whether it needs to join the domain or not
 *
 */
#define DRM_E_DEVICE_DOMAIN_JOIN_REQUIRED ((DRM_RESULT)0x8004C580L)


/* ------------------------------------------------------------
**
** Server errors returned by core logic: error codes from DRM_E_BASECODE+0x600
** to DRM_E_BASECODE+0x6FF, 0x8004c600-0x8004c6ff.
**
** ------------------------------------------------------------
*/

#define DRM_E_SERVER_BASECODE       DRM_E_BASECODE + 0x600

/*
 * MessageId: DRM_E_SERVER_INTERNAL_ERROR
 *
 * MessageText:
 *
 * An internal server error occurred.
 *
 */
#define DRM_E_SERVER_INTERNAL_ERROR      ((DRM_RESULT)0x8004C600L)

/*
 * MessageId: DRM_E_SERVER_INVALID_MESSAGE
 *
 * MessageText:
 *
 * The message sent to the server was invalid.
 *
 */
#define DRM_E_SERVER_INVALID_MESSAGE     ((DRM_RESULT)0x8004C601L)

/*
 * MessageId: DRM_E_SERVER_DEVICE_LIMIT_REACHED
 *
 * MessageText:
 *
 * The device limit for the domain has been reached.
 *
 */
#define DRM_E_SERVER_DEVICE_LIMIT_REACHED ((DRM_RESULT)0x8004C602L)

/*
 * MessageId: DRM_E_SERVER_INDIV_REQUIRED
 *
 * MessageText:
 *
 * Individualization of the client is required.
 *
 */
#define DRM_E_SERVER_INDIV_REQUIRED      ((DRM_RESULT)0x8004C603L)

/*
 * MessageId: DRM_E_SERVER_SERVICE_SPECIFIC
 *
 * MessageText:
 *
 * An error specific to the service has occurred.
 *
 */
#define DRM_E_SERVER_SERVICE_SPECIFIC    ((DRM_RESULT)0x8004C604L)

/*
 * MessageId: DRM_E_SERVER_DOMAIN_REQUIRED
 *
 * MessageText:
 *
 * A Domain certificate is required.
 *
 */
#define DRM_E_SERVER_DOMAIN_REQUIRED     ((DRM_RESULT)0x8004C605L)

/*
 * MessageId: DRM_E_SERVER_RENEW_DOMAIN
 *
 * MessageText:
 *
 * The Domain certificate needs to be renewed.
 *
 */
#define DRM_E_SERVER_RENEW_DOMAIN        ((DRM_RESULT)0x8004C606L)

/*
 * MessageId: DRM_E_SERVER_UNKNOWN_METERINGID
 *
 * MessageText:
 *
 * The metering identifier is unknown.
 *
 */
#define DRM_E_SERVER_UNKNOWN_METERINGID  ((DRM_RESULT)0x8004C607L)

/*
 * MessageId: DRM_E_SERVER_COMPUTER_LIMIT_REACHED
 *
 * MessageText:
 *
 * The computer limit for the domain has been reached.
 *
 */
#define DRM_E_SERVER_COMPUTER_LIMIT_REACHED ((DRM_RESULT)0x8004C608L)

/*
 * MessageId: DRM_E_SERVER_PROTOCOL_FALLBACK
 *
 * MessageText:
 *
 * The client should fallback to the V2 license acquisition protocol.
 *
 */
#define DRM_E_SERVER_PROTOCOL_FALLBACK   ((DRM_RESULT)0x8004C609L)

/*
 * MessageId: DRM_E_SERVER_NOT_A_MEMBER
 *
 * MessageText:
 *
 * The client was removed from the domain in an offline fashion and thus still has a domain cert, but not a valid domain membership.
 *
 */
#define DRM_E_SERVER_NOT_A_MEMBER        ((DRM_RESULT)0x8004C60AL)

/*
 * MessageId: DRM_E_SERVER_PROTOCOL_VERSION_MISMATCH
 *
 * MessageText:
 *
 * The protocol version specified was not supported by the server.
 *
 */
#define DRM_E_SERVER_PROTOCOL_VERSION_MISMATCH ((DRM_RESULT)0x8004C60BL)

/*
 * MessageId: DRM_E_SERVER_UNKNOWN_ACCOUNTID
 *
 * MessageText:
 *
 * The account identifier is unknown.
 *
 */
#define DRM_E_SERVER_UNKNOWN_ACCOUNTID   ((DRM_RESULT)0x8004C60CL)

/*
 * MessageId: DRM_E_SERVER_PROTOCOL_REDIRECT
 *
 * MessageText:
 *
 * The protocol has a redirect.
 *
 */
#define DRM_E_SERVER_PROTOCOL_REDIRECT   ((DRM_RESULT)0x8004C60DL)

/*
 * MessageId: DRM_E_SERVER_UNKNOWN_TRANSACTIONID
 *
 * MessageText:
 *
 * The transaction identifier is unknown.
 *
 */
#define DRM_E_SERVER_UNKNOWN_TRANSACTIONID ((DRM_RESULT)0x8004C610L)

/*
 * MessageId: DRM_E_SERVER_INVALID_LICENSEID
 *
 * MessageText:
 *
 * The license identifier is invalid.
 *
 */
#define DRM_E_SERVER_INVALID_LICENSEID   ((DRM_RESULT)0x8004C611L)

/*
 * MessageId: DRM_E_SERVER_MAXIMUM_LICENSEID_EXCEEDED
 *
 * MessageText:
 *
 * The maximum number of license identifiers in the request was exceeded.
 *
 */
#define DRM_E_SERVER_MAXIMUM_LICENSEID_EXCEEDED ((DRM_RESULT)0x8004C612L)


/* ------------------------------------------------------------
** DRM_E_BASECODE + 0x680 - DRM_E_BASECODE + 0x6ff (0x8004c680-0x8004c6ff)
** are reserved for DRM Services.
**
** See source\common\services\inc\svcerrors.h for Services error codes.
**
** ------------------------------------------------------------
*/

#define DRM_E_SERVICES_BASECODE     (DRM_E_BASECODE + 0x680)

/* ------------------------------------------------------------
**
** License acquisition protocol errors: error codes from DRM_E_BASECODE+0x700
** to DRM_E_BASECODE+0x77F, 0x8004c700-0x8004c77f.
**
** ------------------------------------------------------------
*/

#define DRM_E_LICACQ_BASECODE       DRM_E_BASECODE + 0x700

/*
 * MessageId: DRM_E_LICACQ_TOO_MANY_LICENSES
 *
 * MessageText:
 *
 * There are too many licenses in the license response.
 *
 */
#define DRM_E_LICACQ_TOO_MANY_LICENSES   ((DRM_RESULT)0x8004C700L)

/*
 * MessageId: DRM_E_LICACQ_ACK_TRANSACTION_ID_TOO_BIG
 *
 * MessageText:
 *
 * The Transaction ID specified by the server exceeds the allocated buffer.
 *
 */
#define DRM_E_LICACQ_ACK_TRANSACTION_ID_TOO_BIG ((DRM_RESULT)0x8004C701L)

/*
 * MessageId: DRM_E_LICACQ_ACK_MESSAGE_NOT_CREATED
 *
 * MessageText:
 *
 * The license acquisition acknowledgement message could not be created.
 *
 */
#define DRM_E_LICACQ_ACK_MESSAGE_NOT_CREATED ((DRM_RESULT)0x8004C702L)


/* ------------------------------------------------------------
**
** PlayReady initiator format errors: error codes from DRM_E_BASECODE+0x780
** to DRM_E_BASECODE+0x7FF, 0x8004c780-0x8004c7ff.
**
** ------------------------------------------------------------
*/

#define DRM_E_INITIATORS_BASECODE      DRM_E_BASECODE + 0x780

/*
 * MessageId: DRM_E_INITIATORS_UNKNOWN_TYPE
 *
 * MessageText:
 *
 * The initiator type is unknown.
 *
 */
#define DRM_E_INITIATORS_UNKNOWN_TYPE    ((DRM_RESULT)0x8004C780L)

/*
 * MessageId: DRM_E_INITIATORS_INVALID_SERVICEID
 *
 * MessageText:
 *
 * The service ID data is not valid.
 *
 */
#define DRM_E_INITIATORS_INVALID_SERVICEID ((DRM_RESULT)0x8004C781L)

/*
 * MessageId: DRM_E_INITIATORS_INVALID_ACCOUNTID
 *
 * MessageText:
 *
 * The account ID data is not valid.
 *
 */
#define DRM_E_INITIATORS_INVALID_ACCOUNTID ((DRM_RESULT)0x8004C782L)

/*
 * MessageId: DRM_E_INITIATORS_INVALID_MID
 *
 * MessageText:
 *
 * The account ID data is not valid.
 *
 */
#define DRM_E_INITIATORS_INVALID_MID     ((DRM_RESULT)0x8004C783L)

/*
 * MessageId: DRM_E_INITIATORS_MISSING_DC_URL
 *
 * MessageText:
 *
 * Domain Controller URL is missing.
 *
 */
#define DRM_E_INITIATORS_MISSING_DC_URL  ((DRM_RESULT)0x8004C784L)

/*
 * MessageId: DRM_E_INITIATORS_MISSING_CONTENT_HEADER
 *
 * MessageText:
 *
 * Content header is missing.
 *
 */
#define DRM_E_INITIATORS_MISSING_CONTENT_HEADER ((DRM_RESULT)0x8004C785L)

/*
 * MessageId: DRM_E_INITIATORS_MISSING_LAURL_IN_CONTENT_HEADER
 *
 * MessageText:
 *
 * Missing license acquisition URL in content header.
 *
 */
#define DRM_E_INITIATORS_MISSING_LAURL_IN_CONTENT_HEADER ((DRM_RESULT)0x8004C786L)

/*
 * MessageId: DRM_E_INITIATORS_MISSING_METERCERT_URL
 *
 * MessageText:
 *
 * Meter certificate server URL is missing.
 *
 */
#define DRM_E_INITIATORS_MISSING_METERCERT_URL ((DRM_RESULT)0x8004C787L)


/* ------------------------------------------------------------
**
** Binary certificate errors: error codes from DRM_E_BASECODE+0x800
** to DRM_E_BASECODE+0x8FF, 0x8004c800-0x8004c8ff.
**
** ------------------------------------------------------------
*/

#define DRM_E_BCERT_BASECODE     DRM_E_BASECODE + 0x800

/*
 * MessageId: DRM_E_BCERT_INVALID_SIGNATURE_TYPE
 *
 * MessageText:
 *
 * An invalid signature type was encountered
 *
 */
#define DRM_E_BCERT_INVALID_SIGNATURE_TYPE ((DRM_RESULT)0x8004C800L)

/*
 * MessageId: DRM_E_BCERT_CHAIN_TOO_DEEP
 *
 * MessageText:
 *
 * There are, or there would be, too many certificates in the certificate chain
 *
 */
#define DRM_E_BCERT_CHAIN_TOO_DEEP       ((DRM_RESULT)0x8004C801L)

/*
 * MessageId: DRM_E_BCERT_INVALID_CERT_TYPE
 *
 * MessageText:
 *
 * An invalid certificate type was encountered
 *
 */
#define DRM_E_BCERT_INVALID_CERT_TYPE    ((DRM_RESULT)0x8004C802L)

/*
 * MessageId: DRM_E_BCERT_INVALID_FEATURE
 *
 * MessageText:
 *
 * An invalid feature entry was encountered OR the porting kit was linked with mutually incompatible features or features incompatible with the certificate
 *
 */
#define DRM_E_BCERT_INVALID_FEATURE      ((DRM_RESULT)0x8004C803L)

/*
 * MessageId: DRM_E_BCERT_INVALID_KEY_USAGE
 *
 * MessageText:
 *
 * An invalid public key usage was encountered
 *
 */
#define DRM_E_BCERT_INVALID_KEY_USAGE    ((DRM_RESULT)0x8004C804L)

/*
 * MessageId: DRM_E_BCERT_INVALID_SECURITY_VERSION
 *
 * MessageText:
 *
 * An invalid Indiv Box security version was encountered
 *
 */
#define DRM_E_BCERT_INVALID_SECURITY_VERSION ((DRM_RESULT)0x8004C805L)

/*
 * MessageId: DRM_E_BCERT_INVALID_KEY_TYPE
 *
 * MessageText:
 *
 * An invalid public key type was encountered
 *
 */
#define DRM_E_BCERT_INVALID_KEY_TYPE     ((DRM_RESULT)0x8004C806L)

/*
 * MessageId: DRM_E_BCERT_INVALID_KEY_LENGTH
 *
 * MessageText:
 *
 * An invalid public key length was encountered
 *
 */
#define DRM_E_BCERT_INVALID_KEY_LENGTH   ((DRM_RESULT)0x8004C807L)

/*
 * MessageId: DRM_E_BCERT_INVALID_MAX_LICENSE_SIZE
 *
 * MessageText:
 *
 * An invalid maximum license size value was encountered
 *
 */
#define DRM_E_BCERT_INVALID_MAX_LICENSE_SIZE ((DRM_RESULT)0x8004C808L)

/*
 * MessageId: DRM_E_BCERT_INVALID_MAX_HEADER_SIZE
 *
 * MessageText:
 *
 * An invalid maximum license header size value was encountered
 *
 */
#define DRM_E_BCERT_INVALID_MAX_HEADER_SIZE ((DRM_RESULT)0x8004C809L)

/*
 * MessageId: DRM_E_BCERT_INVALID_MAX_LICENSE_CHAIN_DEPTH
 *
 * MessageText:
 *
 * An invalid maximum license chain depth was encountered
 *
 */
#define DRM_E_BCERT_INVALID_MAX_LICENSE_CHAIN_DEPTH ((DRM_RESULT)0x8004C80AL)

/*
 * MessageId: DRM_E_BCERT_INVALID_SECURITY_LEVEL
 *
 * MessageText:
 *
 * An invalid security level was encountered
 *
 */
#define DRM_E_BCERT_INVALID_SECURITY_LEVEL ((DRM_RESULT)0x8004C80BL)

/*
 * MessageId: DRM_E_BCERT_PRIVATE_KEY_NOT_SPECIFIED
 *
 * MessageText:
 *
 * A private key for signing the certificate was not provided to the builder
 *
 */
#define DRM_E_BCERT_PRIVATE_KEY_NOT_SPECIFIED ((DRM_RESULT)0x8004C80CL)

/*
 * MessageId: DRM_E_BCERT_ISSUER_KEY_NOT_SPECIFIED
 *
 * MessageText:
 *
 * An issuer key was not provided to the builder
 *
 */
#define DRM_E_BCERT_ISSUER_KEY_NOT_SPECIFIED ((DRM_RESULT)0x8004C80DL)

/*
 * MessageId: DRM_E_BCERT_ACCOUNT_ID_NOT_SPECIFIED
 *
 * MessageText:
 *
 * An account ID was not provided to the builder
 *
 */
#define DRM_E_BCERT_ACCOUNT_ID_NOT_SPECIFIED ((DRM_RESULT)0x8004C80EL)

/*
 * MessageId: DRM_E_BCERT_SERVICE_ID_NOT_SPECIFIED
 *
 * MessageText:
 *
 * A service provider ID was not provided to the builder
 *
 */
#define DRM_E_BCERT_SERVICE_ID_NOT_SPECIFIED ((DRM_RESULT)0x8004C80FL)

/*
 * MessageId: DRM_E_BCERT_DOMAIN_URL_NOT_SPECIFIED
 *
 * MessageText:
 *
 * A domain URL was not provided to the builder
 *
 */
#define DRM_E_BCERT_DOMAIN_URL_NOT_SPECIFIED ((DRM_RESULT)0x8004C811L)

/*
 * MessageId: DRM_E_BCERT_DOMAIN_URL_TOO_LONG
 *
 * MessageText:
 *
 * The domain URL contains too many ASCII characters
 *
 */
#define DRM_E_BCERT_DOMAIN_URL_TOO_LONG  ((DRM_RESULT)0x8004C812L)

/*
 * MessageId: DRM_E_BCERT_HARDWARE_ID_TOO_LONG
 *
 * MessageText:
 *
 * A hardware ID is longer than the maximum supported bytes
 *
 */
#define DRM_E_BCERT_HARDWARE_ID_TOO_LONG ((DRM_RESULT)0x8004C814L)

/*
 * MessageId: DRM_E_BCERT_CERT_ID_NOT_SPECIFIED
 *
 * MessageText:
 *
 * A certificate ID was not provided to the builder
 *
 */
#define DRM_E_BCERT_CERT_ID_NOT_SPECIFIED ((DRM_RESULT)0x8004C816L)

/*
 * MessageId: DRM_E_BCERT_PUBLIC_KEY_NOT_SPECIFIED
 *
 * MessageText:
 *
 * A public key for the certificate was not provided to the builder or not found by the parser
 *
 */
#define DRM_E_BCERT_PUBLIC_KEY_NOT_SPECIFIED ((DRM_RESULT)0x8004C817L)

/*
 * MessageId: DRM_E_BCERT_KEY_USAGES_NOT_SPECIFIED
 *
 * MessageText:
 *
 * The public key usage information was not provided to the builder or not found by the parser
 *
 */
#define DRM_E_BCERT_KEY_USAGES_NOT_SPECIFIED ((DRM_RESULT)0x8004C818L)

/*
 * MessageId: DRM_E_BCERT_STRING_NOT_NULL_TERMINATED
 *
 * MessageText:
 *
 * Data string is not null-teminated
 *
 */
#define DRM_E_BCERT_STRING_NOT_NULL_TERMINATED ((DRM_RESULT)0x8004C819L)

/*
 * MessageId: DRM_E_BCERT_OBJECTHEADER_LEN_TOO_BIG
 *
 * MessageText:
 *
 * Object length in object header is too big
 *
 */
#define DRM_E_BCERT_OBJECTHEADER_LEN_TOO_BIG ((DRM_RESULT)0x8004C81AL)

/*
 * MessageId: DRM_E_BCERT_INVALID_ISSUERKEY_LENGTH
 *
 * MessageText:
 *
 * IssuerKey Length value is invalid
 *
 */
#define DRM_E_BCERT_INVALID_ISSUERKEY_LENGTH ((DRM_RESULT)0x8004C81BL)

/*
 * MessageId: DRM_E_BCERT_BASICINFO_CERT_EXPIRED
 *
 * MessageText:
 *
 * Certificate is expired
 *
 */
#define DRM_E_BCERT_BASICINFO_CERT_EXPIRED ((DRM_RESULT)0x8004C81CL)

/*
 * MessageId: DRM_E_BCERT_UNEXPECTED_OBJECT_HEADER
 *
 * MessageText:
 *
 * Object header has unexpected values
 *
 */
#define DRM_E_BCERT_UNEXPECTED_OBJECT_HEADER ((DRM_RESULT)0x8004C81DL)

/*
 * MessageId: DRM_E_BCERT_ISSUERKEY_KEYINFO_MISMATCH
 *
 * MessageText:
 *
 * The cert's Issuer Key does not match key info in the next cert
 *
 */
#define DRM_E_BCERT_ISSUERKEY_KEYINFO_MISMATCH ((DRM_RESULT)0x8004C81EL)

/*
 * MessageId: DRM_E_BCERT_INVALID_MAX_KEY_USAGES
 *
 * MessageText:
 *
 * Number of key usage entries is invalid
 *
 */
#define DRM_E_BCERT_INVALID_MAX_KEY_USAGES ((DRM_RESULT)0x8004C81FL)

/*
 * MessageId: DRM_E_BCERT_INVALID_MAX_FEATURES
 *
 * MessageText:
 *
 * Number of features is invalid
 *
 */
#define DRM_E_BCERT_INVALID_MAX_FEATURES ((DRM_RESULT)0x8004C820L)

/*
 * MessageId: DRM_E_BCERT_INVALID_CHAIN_HEADER_TAG
 *
 * MessageText:
 *
 * Cert chain header tag is invalid
 *
 */
#define DRM_E_BCERT_INVALID_CHAIN_HEADER_TAG ((DRM_RESULT)0x8004C821L)

/*
 * MessageId: DRM_E_BCERT_INVALID_CHAIN_VERSION
 *
 * MessageText:
 *
 * Cert chain version is invalid
 *
 */
#define DRM_E_BCERT_INVALID_CHAIN_VERSION ((DRM_RESULT)0x8004C822L)

/*
 * MessageId: DRM_E_BCERT_INVALID_CHAIN_LENGTH
 *
 * MessageText:
 *
 * Cert chain length value is invalid
 *
 */
#define DRM_E_BCERT_INVALID_CHAIN_LENGTH ((DRM_RESULT)0x8004C823L)

/*
 * MessageId: DRM_E_BCERT_INVALID_CERT_HEADER_TAG
 *
 * MessageText:
 *
 * Cert header tag is invalid
 *
 */
#define DRM_E_BCERT_INVALID_CERT_HEADER_TAG ((DRM_RESULT)0x8004C824L)

/*
 * MessageId: DRM_E_BCERT_INVALID_CERT_VERSION
 *
 * MessageText:
 *
 * Cert version is invalid
 *
 */
#define DRM_E_BCERT_INVALID_CERT_VERSION ((DRM_RESULT)0x8004C825L)

/*
 * MessageId: DRM_E_BCERT_INVALID_CERT_LENGTH
 *
 * MessageText:
 *
 * Cert length value is invalid
 *
 */
#define DRM_E_BCERT_INVALID_CERT_LENGTH  ((DRM_RESULT)0x8004C826L)

/*
 * MessageId: DRM_E_BCERT_INVALID_SIGNEDCERT_LENGTH
 *
 * MessageText:
 *
 * Length of signed portion of certificate is invalid
 *
 */
#define DRM_E_BCERT_INVALID_SIGNEDCERT_LENGTH ((DRM_RESULT)0x8004C827L)

/*
 * MessageId: DRM_E_BCERT_INVALID_PLATFORM_IDENTIFIER
 *
 * MessageText:
 *
 * An invalid Platform Identifier was specified
 *
 */
#define DRM_E_BCERT_INVALID_PLATFORM_IDENTIFIER ((DRM_RESULT)0x8004C828L)

/*
 * MessageId: DRM_E_BCERT_INVALID_NUMBER_EXTDATARECORDS
 *
 * MessageText:
 *
 * An invalid number of extended data records
 *
 */
#define DRM_E_BCERT_INVALID_NUMBER_EXTDATARECORDS ((DRM_RESULT)0x8004C829L)

/*
 * MessageId: DRM_E_BCERT_INVALID_EXTDATARECORD
 *
 * MessageText:
 *
 * An invalid extended data record
 *
 */
#define DRM_E_BCERT_INVALID_EXTDATARECORD ((DRM_RESULT)0x8004C82AL)

/*
 * MessageId: DRM_E_BCERT_EXTDATA_LENGTH_MUST_PRESENT
 *
 * MessageText:
 *
 * Extended data record length must be present.
 *
 */
#define DRM_E_BCERT_EXTDATA_LENGTH_MUST_PRESENT ((DRM_RESULT)0x8004C82BL)

/*
 * MessageId: DRM_E_BCERT_EXTDATA_PRIVKEY_MUST_PRESENT
 *
 * MessageText:
 *
 * Extended data record length must be present.
 *
 */
#define DRM_E_BCERT_EXTDATA_PRIVKEY_MUST_PRESENT ((DRM_RESULT)0x8004C82CL)

/*
 * MessageId: DRM_E_BCERT_INVALID_EXTDATA_LENGTH
 *
 * MessageText:
 *
 * Calculated and written extended data object lengths do not match.
 *
 */
#define DRM_E_BCERT_INVALID_EXTDATA_LENGTH ((DRM_RESULT)0x8004C82DL)

/*
 * MessageId: DRM_E_BCERT_EXTDATA_IS_NOT_PROVIDED
 *
 * MessageText:
 *
 * Extended data is not provided, the cert builder cannot write it.
 *
 */
#define DRM_E_BCERT_EXTDATA_IS_NOT_PROVIDED ((DRM_RESULT)0x8004C82EL)

/*
 * MessageId: DRM_E_BCERT_HWIDINFO_IS_MISSING
 *
 * MessageText:
 *
 * The PC certificate is correct but is not ready to use because has no HWID information
 *
 */
#define DRM_E_BCERT_HWIDINFO_IS_MISSING  ((DRM_RESULT)0x8004C82FL)

/*
 * MessageId: DRM_E_BCERT_EXTDATAFLAG_CERT_TYPE_MISMATCH
 *
 * MessageText:
 *
 * Certificate of this type cannot have extended data flag set
 *
 */
#define DRM_E_BCERT_EXTDATAFLAG_CERT_TYPE_MISMATCH ((DRM_RESULT)0x8004C832L)

/*
 * MessageId: DRM_E_BCERT_METERING_ID_NOT_SPECIFIED
 *
 * MessageText:
 *
 * An metering ID was not provided to the builder
 *
 */
#define DRM_E_BCERT_METERING_ID_NOT_SPECIFIED ((DRM_RESULT)0x8004C833L)

/*
 * MessageId: DRM_E_BCERT_METERING_URL_NOT_SPECIFIED
 *
 * MessageText:
 *
 * A metering URL was not provided to the builder
 *
 */
#define DRM_E_BCERT_METERING_URL_NOT_SPECIFIED ((DRM_RESULT)0x8004C834L)

/*
 * MessageId: DRM_E_BCERT_METERING_URL_TOO_LONG
 *
 * MessageText:
 *
 * The metering URL contains too many ASCII characters
 *
 */
#define DRM_E_BCERT_METERING_URL_TOO_LONG ((DRM_RESULT)0x8004C835L)

/*
 * MessageId: DRM_E_BCERT_VERIFICATION_ERRORS
 *
 * MessageText:
 *
 * Verification errors are found while parsing cert chain
 *
 */
#define DRM_E_BCERT_VERIFICATION_ERRORS  ((DRM_RESULT)0x8004C836L)

/*
 * MessageId: DRM_E_BCERT_REQUIRED_KEYUSAGE_MISSING
 *
 * MessageText:
 *
 * Required key usage is missing
 *
 */
#define DRM_E_BCERT_REQUIRED_KEYUSAGE_MISSING ((DRM_RESULT)0x8004C837L)

/*
 * MessageId: DRM_E_BCERT_NO_PUBKEY_WITH_REQUESTED_KEYUSAGE
 *
 * MessageText:
 *
 * The certificate does not contain a public key with the requested key usage
 *
 */
#define DRM_E_BCERT_NO_PUBKEY_WITH_REQUESTED_KEYUSAGE ((DRM_RESULT)0x8004C838L)

/*
 * MessageId: DRM_E_BCERT_MANUFACTURER_STRING_TOO_LONG
 *
 * MessageText:
 *
 * The manufacturer string is too long
 *
 */
#define DRM_E_BCERT_MANUFACTURER_STRING_TOO_LONG ((DRM_RESULT)0x8004C839L)

/*
 * MessageId: DRM_E_BCERT_TOO_MANY_PUBLIC_KEYS
 *
 * MessageText:
 *
 * There are too many public keys in the certificate
 *
 */
#define DRM_E_BCERT_TOO_MANY_PUBLIC_KEYS ((DRM_RESULT)0x8004C83AL)

/*
 * MessageId: DRM_E_BCERT_OBJECTHEADER_LEN_TOO_SMALL
 *
 * MessageText:
 *
 * Object length in object header is too small
 *
 */
#define DRM_E_BCERT_OBJECTHEADER_LEN_TOO_SMALL ((DRM_RESULT)0x8004C83BL)

/*
 * MessageId: DRM_E_BCERT_INVALID_WARNING_DAYS
 *
 * MessageText:
 *
 * An invalid server certificate expiration warning days. Warning days must be greater than zero.
 *
 */
#define DRM_E_BCERT_INVALID_WARNING_DAYS ((DRM_RESULT)0x8004C83CL)


/* ------------------------------------------------------------
**
** XML Signature/Encryption errors: error codes from DRM_E_BASECODE+0x900
** to DRM_E_BASECODE+0x9FF, 0x8004c900-0x8004c9ff.
**
** ------------------------------------------------------------
*/

#define DRM_E_XMLSIG_BASECODE       DRM_E_BASECODE + 0x900

/*
 * MessageId: DRM_E_XMLSIG_ECDSA_VERIFY_FAILURE
 *
 * MessageText:
 *
 * Error in ECDSA signature verification.
 *
 */
#define DRM_E_XMLSIG_ECDSA_VERIFY_FAILURE ((DRM_RESULT)0x8004C900L)

/*
 * MessageId: DRM_E_XMLSIG_SHA_VERIFY_FAILURE
 *
 * MessageText:
 *
 * Error in SHA verification.
 *
 */
#define DRM_E_XMLSIG_SHA_VERIFY_FAILURE  ((DRM_RESULT)0x8004C901L)

/*
 * MessageId: DRM_E_XMLSIG_FORMAT
 *
 * MessageText:
 *
 * The format of XML signature or encryption segment is incorrect.
 *
 */
#define DRM_E_XMLSIG_FORMAT              ((DRM_RESULT)0x8004C902L)

/*
 * MessageId: DRM_E_XMLSIG_PUBLIC_KEY_ID
 *
 * MessageText:
 *
 * Invalud pre-shared public key ID.
 *
 */
#define DRM_E_XMLSIG_PUBLIC_KEY_ID       ((DRM_RESULT)0x8004C903L)

/*
 * MessageId: DRM_E_XMLSIG_INVALID_KEY_FORMAT
 *
 * MessageText:
 *
 * Invalid type of public/private key format.
 *
 */
#define DRM_E_XMLSIG_INVALID_KEY_FORMAT  ((DRM_RESULT)0x8004C904L)

/*
 * MessageId: DRM_E_XMLSIG_SHA_HASH_SIZE
 *
 * MessageText:
 *
 * Size of hash is unexpected.
 *
 */
#define DRM_E_XMLSIG_SHA_HASH_SIZE       ((DRM_RESULT)0x8004C905L)

/*
 * MessageId: DRM_E_XMLSIG_ECDSA_SIGNATURE_SIZE
 *
 * MessageText:
 *
 * Size of ECDSA signature is unexpected.
 *
 */
#define DRM_E_XMLSIG_ECDSA_SIGNATURE_SIZE ((DRM_RESULT)0x8004C906L)


/* ------------------------------------------------------------
**
** UTF8 encoding errors: error codes from DRM_E_BASECODE+0xA00
** to DRM_E_BASECODE+0xAFF, 0x8004ca00-0x8004caff.
**
** ------------------------------------------------------------
*/

#define DRM_E_UTF_BASECODE       DRM_E_BASECODE + 0xa00

/*
 * MessageId: DRM_E_UTF_UNEXPECTED_END
 *
 * MessageText:
 *
 * Unexpected end of data in the middle of multibyte character.
 *
 */
#define DRM_E_UTF_UNEXPECTED_END         ((DRM_RESULT)0x8004CA00L)

/*
 * MessageId: DRM_E_UTF_INVALID_CODE
 *
 * MessageText:
 *
 * UTF character maps into a code with invalid value.
 *
 */
#define DRM_E_UTF_INVALID_CODE           ((DRM_RESULT)0x8004CA01L)


/* ------------------------------------------------------------
**
** XML SOAP errors: error codes from DRM_E_BASECODE+0xB00
** to DRM_E_BASECODE+0xBFF, 0x8004cb00-0x8004cbff.
**
** ------------------------------------------------------------
*/

#define DRM_E_SOAPXML_BASECODE       DRM_E_BASECODE + 0xb00

/*
 * MessageId: DRM_E_SOAPXML_INVALID_STATUS_CODE
 *
 * MessageText:
 *
 * Status code contained in the server error response is invalid.
 *
 */
#define DRM_E_SOAPXML_INVALID_STATUS_CODE ((DRM_RESULT)0x8004CB00L)

/*
 * MessageId: DRM_E_SOAPXML_XML_FORMAT
 *
 * MessageText:
 *
 * Cannot parse out expected XML node.
 *
 */
#define DRM_E_SOAPXML_XML_FORMAT         ((DRM_RESULT)0x8004CB01L)

/*
 * MessageId: DRM_E_SOAPXML_WRONG_MESSAGE_TYPE
 *
 * MessageText:
 *
 * The message type associated with the soap message is wrong.
 *
 */
#define DRM_E_SOAPXML_WRONG_MESSAGE_TYPE ((DRM_RESULT)0x8004CB02L)

/*
 * MessageId: DRM_E_SOAPXML_SIGNATURE_MISSING
 *
 * MessageText:
 *
 * The message did not have a signature and needed one
 *
 */
#define DRM_E_SOAPXML_SIGNATURE_MISSING  ((DRM_RESULT)0x8004CB03L)

/*
 * MessageId: DRM_E_SOAPXML_PROTOCOL_NOT_SUPPORTED
 *
 * MessageText:
 *
 * The requested protocol is not supported by the DRM SOAP parser.
 *
 */
#define DRM_E_SOAPXML_PROTOCOL_NOT_SUPPORTED ((DRM_RESULT)0x8004CB04L)

/*
 * MessageId: DRM_E_SOAPXML_DATA_NOT_FOUND
 *
 * MessageText:
 *
 * The requested data is not found in the response.
 *
 */
#define DRM_E_SOAPXML_DATA_NOT_FOUND     ((DRM_RESULT)0x8004CB05L)


/* ------------------------------------------------------------
**
** Generic crypto errors: error codes from DRM_E_BASECODE+0xC00
** to DRM_E_BASECODE+0xCFF, 0x8004cc00-0x8004ccff.
**
** ------------------------------------------------------------
*/

#define DRM_E_CRYPTO_BASECODE       DRM_E_BASECODE + 0xc00

/*
 * MessageId: DRM_E_CRYPTO_PUBLIC_KEY_NOT_MATCH
 *
 * MessageText:
 *
 * The public key associated with an encrypted domain private from the server does not match any public key on the device.
 *
 */
#define DRM_E_CRYPTO_PUBLIC_KEY_NOT_MATCH ((DRM_RESULT)0x8004CC00L)

/*
 * MessageId: DRM_E_UNABLE_TO_RESOLVE_LOCATION_TREE
 *
 * MessageText:
 *
 * Unable to derive the key.  Maybe due to blackout or no rights to the service, etc.
 *
 */
#define DRM_E_UNABLE_TO_RESOLVE_LOCATION_TREE ((DRM_RESULT)0x8004CC01L)


/* ------------------------------------------------------------
**
** NDT/NDR results: error codes from DRM_E_BASECODE+0xE00
** to DRM_E_BASECODE+0xEFF, 0x8004ce00-0x8004ceff.
**
** ------------------------------------------------------------
*/

#define DRM_ND_BASECODE           DRM_E_BASECODE + 0xE00

/*
 * MessageId: DRM_E_ND_MUST_REVALIDATE
 *
 * MessageText:
 *
 * The client must be revalidated before executing the intended operation.
 *
 */
#define DRM_E_ND_MUST_REVALIDATE         ((DRM_RESULT)0x8004CE00L)

/*
 * MessageId: DRM_E_ND_INVALID_MESSAGE
 *
 * MessageText:
 *
 * A received message is garbled.
 *
 */
#define DRM_E_ND_INVALID_MESSAGE         ((DRM_RESULT)0x8004CE01L)

/*
 * MessageId: DRM_E_ND_INVALID_MESSAGE_TYPE
 *
 * MessageText:
 *
 * A received message contains an invalid message type.
 *
 */
#define DRM_E_ND_INVALID_MESSAGE_TYPE    ((DRM_RESULT)0x8004CE02L)

/*
 * MessageId: DRM_E_ND_INVALID_MESSAGE_VERSION
 *
 * MessageText:
 *
 * A received message contains an invalid message version.
 *
 */
#define DRM_E_ND_INVALID_MESSAGE_VERSION ((DRM_RESULT)0x8004CE03L)

/*
 * MessageId: DRM_E_ND_INVALID_SESSION
 *
 * MessageText:
 *
 * The requested session is invalid.
 *
 */
#define DRM_E_ND_INVALID_SESSION         ((DRM_RESULT)0x8004CE04L)

/*
 * MessageId: DRM_E_ND_MEDIA_SESSION_LIMIT_REACHED
 *
 * MessageText:
 *
 * A new session cannot be opened because the maximum number of sessions has already been opened.
 *
 */
#define DRM_E_ND_MEDIA_SESSION_LIMIT_REACHED ((DRM_RESULT)0x8004CE05L)

/*
 * MessageId: DRM_E_ND_UNABLE_TO_VERIFY_PROXIMITY
 *
 * MessageText:
 *
 * The proximity detection procedure could not confirm that the receiver is near the transmitter in the network.
 *
 */
#define DRM_E_ND_UNABLE_TO_VERIFY_PROXIMITY ((DRM_RESULT)0x8004CE06L)

/*
 * MessageId: DRM_E_ND_INVALID_PROXIMITY_RESPONSE
 *
 * MessageText:
 *
 * The response to the proximity detection challenge is invalid.
 *
 */
#define DRM_E_ND_INVALID_PROXIMITY_RESPONSE ((DRM_RESULT)0x8004CE07L)

/*
 * MessageId: DRM_E_ND_DEVICE_LIMIT_REACHED
 *
 * MessageText:
 *
 * The maximum number of devices in use has been reached. Unable to open additional devices.
 *
 */
#define DRM_E_ND_DEVICE_LIMIT_REACHED    ((DRM_RESULT)0x8004CE08L)

/*
 * MessageId: DRM_E_ND_BAD_REQUEST
 *
 * MessageText:
 *
 * The message format is invalid.
 *
 */
#define DRM_E_ND_BAD_REQUEST             ((DRM_RESULT)0x8004CE09L)

/*
 * MessageId: DRM_E_ND_FAILED_SEEK
 *
 * MessageText:
 *
 * It is not possible to seek to the specified mark-in point.
 *
 */
#define DRM_E_ND_FAILED_SEEK             ((DRM_RESULT)0x8004CE0AL)

/*
 * MessageId: DRM_E_ND_INVALID_CONTEXT
 *
 * MessageText:
 *
 * Manager context or at least one of it's children is missing (or corrupt).
 *
 */
#define DRM_E_ND_INVALID_CONTEXT         ((DRM_RESULT)0x8004CE0BL)


/* ------------------------------------------------------------
**
** ASF results: error codes from DRM_E_BASECODE+0xF00
** to DRM_E_BASECODE+0xFFF, 0x8004ce00-0x8004cfff.
**
** ------------------------------------------------------------
*/

#define DRM_ASF_BASECODE           DRM_E_BASECODE + 0xF00

/* ASF Parsing Errors */
/* ------------------ */

/*
 * MessageId: DRM_E_ASF_BAD_ASF_HEADER
 *
 * MessageText:
 *
 * The ASF file has a bad ASF header.
 *
 */
#define DRM_E_ASF_BAD_ASF_HEADER         ((DRM_RESULT)0x8004CF00L)

/*
 * MessageId: DRM_E_ASF_BAD_PACKET_HEADER
 *
 * MessageText:
 *
 * The ASF file has a bad packet header.
 *
 */
#define DRM_E_ASF_BAD_PACKET_HEADER      ((DRM_RESULT)0x8004CF01L)

/*
 * MessageId: DRM_E_ASF_BAD_PAYLOAD_HEADER
 *
 * MessageText:
 *
 * The ASF file has a bad payload header.
 *
 */
#define DRM_E_ASF_BAD_PAYLOAD_HEADER     ((DRM_RESULT)0x8004CF02L)

/*
 * MessageId: DRM_E_ASF_BAD_DATA_HEADER
 *
 * MessageText:
 *
 * The ASF file has a bad data header.
 *
 */
#define DRM_E_ASF_BAD_DATA_HEADER        ((DRM_RESULT)0x8004CF03L)

/*
 * MessageId: DRM_E_ASF_INVALID_OPERATION
 *
 * MessageText:
 *
 * The intended operation is invalid given the current processing state of the ASF file.
 *
 */
#define DRM_E_ASF_INVALID_OPERATION      ((DRM_RESULT)0x8004CF04L)

/*
 * MessageId: DRM_E_ASF_EXTENDED_STREAM_PROPERTIES_OBJ_NOT_FOUND
 *
 * MessageText:
 *
 * Extended stream properties object is not found; the file may be in non-supported outdated format.
 *
 */
#define DRM_E_ASF_EXTENDED_STREAM_PROPERTIES_OBJ_NOT_FOUND ((DRM_RESULT)0x8004CF06L)


/* ASF Muxing Errors */
/* ----------------- */

/*
 * MessageId: DRM_E_ASF_INVALID_DATA
 *
 * MessageText:
 *
 * The packet is overstuffed with data.
 *
 */
#define DRM_E_ASF_INVALID_DATA           ((DRM_RESULT)0x8004CF20L)

/*
 * MessageId: DRM_E_ASF_TOO_MANY_PAYLOADS
 *
 * MessageText:
 *
 * The number of payloads in the packet is greater than the maximum allowed.
 *
 */
#define DRM_E_ASF_TOO_MANY_PAYLOADS      ((DRM_RESULT)0x8004CF21L)

/*
 * MessageId: DRM_E_ASF_BANDWIDTH_OVERRUN
 *
 * MessageText:
 *
 * An object is overflowing the leaky bucket.
 *
 */
#define DRM_E_ASF_BANDWIDTH_OVERRUN      ((DRM_RESULT)0x8004CF22L)

/*
 * MessageId: DRM_E_ASF_INVALID_STREAM_NUMBER
 *
 * MessageText:
 *
 * The stream number is invalid; it is either zero, greater than the maximum value allowed, or has no associated data.
 *
 */
#define DRM_E_ASF_INVALID_STREAM_NUMBER  ((DRM_RESULT)0x8004CF23L)

/*
 * MessageId: DRM_E_ASF_LATE_SAMPLE
 *
 * MessageText:
 *
 * A sample was encountered with a presentation time outside of the mux's send window.
 *
 */
#define DRM_E_ASF_LATE_SAMPLE            ((DRM_RESULT)0x8004CF24L)

/*
 * MessageId: DRM_E_ASF_NOT_ACCEPTING
 *
 * MessageText:
 *
 * The sample does not fit in the remaining payload space.
 *
 */
#define DRM_E_ASF_NOT_ACCEPTING          ((DRM_RESULT)0x8004CF25L)

/*
 * MessageId: DRM_E_ASF_UNEXPECTED
 *
 * MessageText:
 *
 * An unexpected error occurred.
 *
 */
#define DRM_E_ASF_UNEXPECTED             ((DRM_RESULT)0x8004CF26L)


/* ------------------------------------------------------------
**
** Nonce store errors: error codes from DRM_E_BASECODE+0x1000
** to DRM_E_BASECODE+0x10FF, 0x8004d000-0x8004d0ff.
**
** ------------------------------------------------------------
*/

#define DRM_E_NONCE_STORE_BASECODE       DRM_E_BASECODE + 0x1000

/*
 * MessageId: DRM_E_NONCE_STORE_TOKEN_NOT_FOUND
 *
 * MessageText:
 *
 * The matching nonce store token is not found.
 *
 */
#define DRM_E_NONCE_STORE_TOKEN_NOT_FOUND ((DRM_RESULT)0x8004D000L)

/*
 * MessageId: DRM_E_NONCE_STORE_OPEN_STORE
 *
 * MessageText:
 *
 * Fail to open nonce store.
 *
 */
#define DRM_E_NONCE_STORE_OPEN_STORE     ((DRM_RESULT)0x8004D001L)

/*
 * MessageId: DRM_E_NONCE_STORE_CLOSE_STORE
 *
 * MessageText:
 *
 * Fail to close nonce store.
 *
 */
#define DRM_E_NONCE_STORE_CLOSE_STORE    ((DRM_RESULT)0x8004D002L)

/*
 * MessageId: DRM_E_NONCE_STORE_ADD_LICENSE
 *
 * MessageText:
 *
 * There is already a license associated with the nonce store token.
 *
 */
#define DRM_E_NONCE_STORE_ADD_LICENSE    ((DRM_RESULT)0x8004D003L)


/* ------------------------------------------------------------
**
** Policy State errors: error codes from DRM_E_BASECODE+0x1200 to
** DRM_E_BASECODE+0x12FF, 0x8004d200-0x8004d2ff.
**
** ------------------------------------------------------------
*/

#define DRM_E_POLICYSTATE_BASECODE              DRM_E_BASECODE+0x1200

/*
 * MessageId: DRM_E_POLICYSTATE_NOT_FOUND
 *
 * MessageText:
 *
 * The policy state is not found in the secure store.
 *
 */
#define DRM_E_POLICYSTATE_NOT_FOUND      ((DRM_RESULT)0x8004D200L)

/*
 * MessageId: DRM_E_POLICYSTATE_CORRUPTED
 *
 * MessageText:
 *
 * The policy state is not stored as a valid internal format in the secure store.
 *
 */
#define DRM_E_POLICYSTATE_CORRUPTED      ((DRM_RESULT)0x8004D201L)


/* ------------------------------------------------------------
**
** Move errors: error codes from DRM_E_BASECODE+0x1300 to
** DRM_E_BASECODE+0x13FF, 0x8004d300-0x8004d3ff.
**
** ------------------------------------------------------------
*/

#define DRM_E_MOVE_BASECODE              DRM_E_BASECODE+0x1300

/*
 * MessageId: DRM_E_MOVE_DENIED
 *
 * MessageText:
 *
 * The requested move operation was denied by the service.
 *
 */
#define DRM_E_MOVE_DENIED                ((DRM_RESULT)0x8004D300L)

/*
 * MessageId: DRM_E_INVALID_MOVE_RESPONSE
 *
 * MessageText:
 *
 * The move response was incorrectly formed.
 *
 */
#define DRM_E_INVALID_MOVE_RESPONSE      ((DRM_RESULT)0x8004D301L)

/*
 * MessageId: DRM_E_MOVE_NONCE_MISMATCH
 *
 * MessageText:
 *
 * The nonce in the repsonse did not match the expected value.
 *
 */
#define DRM_E_MOVE_NONCE_MISMATCH        ((DRM_RESULT)0x8004D302L)

/*
 * MessageId: DRM_E_MOVE_STORE_OPEN_STORE
 *
 * MessageText:
 *
 * Failed to open the move store.
 *
 */
#define DRM_E_MOVE_STORE_OPEN_STORE      ((DRM_RESULT)0x8004D304L)

/*
 * MessageId: DRM_E_MOVE_STORE_CLOSE_STORE
 *
 * MessageText:
 *
 * Failed to close the move store.
 *
 */
#define DRM_E_MOVE_STORE_CLOSE_STORE     ((DRM_RESULT)0x8004D305L)

/*
 * MessageId: DRM_E_MOVE_STORE_ADD_DATA
 *
 * MessageText:
 *
 * Failed to add data into the move store.
 *
 */
#define DRM_E_MOVE_STORE_ADD_DATA        ((DRM_RESULT)0x8004D306L)

/*
 * MessageId: DRM_E_MOVE_STORE_GET_DATA
 *
 * MessageText:
 *
 * Failed to retrieve data from the move store.
 *
 */
#define DRM_E_MOVE_STORE_GET_DATA        ((DRM_RESULT)0x8004D307L)

/*
 * MessageId: DRM_E_MOVE_FORMAT_INVALID
 *
 * MessageText:
 *
 * The format of a move page or index is invalid.
 *
 */
#define DRM_E_MOVE_FORMAT_INVALID        ((DRM_RESULT)0x8004D308L)

/*
 * MessageId: DRM_E_MOVE_SIGNATURE_INVALID
 *
 * MessageText:
 *
 * The signature of a move index is invalid.
 *
 */
#define DRM_E_MOVE_SIGNATURE_INVALID     ((DRM_RESULT)0x8004D309L)

/*
 * MessageId: DRM_E_COPY_DENIED
 *
 * MessageText:
 *
 * The requested copy operation was denied by the service.
 *
 */
#define DRM_E_COPY_DENIED                ((DRM_RESULT)0x8004D30AL)

/* ------------------------------------------------------------
**
** Extensible Binary errors: error codes from DRM_E_BASECODE+0x1400 to
** DRM_E_BASECODE+0x14FF, 0x8004d400-0x8004d4ff.
**
** ------------------------------------------------------------
*/

#define DRM_E_XB_BASECODE              DRM_E_BASECODE+0x1400

/*
 * MessageId: DRM_E_XB_OBJECT_NOTFOUND
 *
 * MessageText:
 *
 * The extensible binary object was not found.
 *
 */
#define DRM_E_XB_OBJECT_NOTFOUND         ((DRM_RESULT)0x8004D400L)

/*
 * MessageId: DRM_E_XB_INVALID_OBJECT
 *
 * MessageText:
 *
 * The extensible binary object format was invalid.
 *
 */
#define DRM_E_XB_INVALID_OBJECT          ((DRM_RESULT)0x8004D401L)

/*
 * MessageId: DRM_E_XB_OBJECT_ALREADY_EXISTS
 *
 * MessageText:
 *
 * A single instance extensible binary object was encountered more than once.
 *
 */
#define DRM_E_XB_OBJECT_ALREADY_EXISTS   ((DRM_RESULT)0x8004D402L)

/*
 * MessageId: DRM_E_XB_REQUIRED_OBJECT_MISSING
 *
 * MessageText:
 *
 * A required extensible binary object was not found during building.
 *
 */
#define DRM_E_XB_REQUIRED_OBJECT_MISSING ((DRM_RESULT)0x8004D403L)

/*
 * MessageId: DRM_E_XB_UNKNOWN_ELEMENT_TYPE
 *
 * MessageText:
 *
 * An extensible binary object description contained an element of an unknown type.
 *
 */
#define DRM_E_XB_UNKNOWN_ELEMENT_TYPE    ((DRM_RESULT)0x8004D404L)

/* ------------------------------------------------------------
**
** Keyfile errors: error codes from DRM_E_BASECODE+0x1500 to
** DRM_E_BASECODE+0x15FF, 0x8004d500-0x8004d5ff.
**
** ------------------------------------------------------------
*/

#define DRM_E_KEYFILE_BASECODE              DRM_E_BASECODE+0x1500

/*
 * MessageId: DRM_E_KEYFILE_INVALID_PLATFORM
 *
 * MessageText:
 *
 * The keyfile does not support the current platform.
 *
 */
#define DRM_E_KEYFILE_INVALID_PLATFORM   ((DRM_RESULT)0x8004D500L)

/*
 * MessageId: DRM_E_KEYFILE_TOO_LARGE
 *
 * MessageText:
 *
 * The keyfile is larger than the maximum supported size.
 *
 */
#define DRM_E_KEYFILE_TOO_LARGE          ((DRM_RESULT)0x8004D501L)

/*
 * MessageId: DRM_E_KEYFILE_PRIVATE_KEY_NOT_FOUND
 *
 * MessageText:
 *
 * The private key requested was not found in the keyfile.
 *
 */
#define DRM_E_KEYFILE_PRIVATE_KEY_NOT_FOUND ((DRM_RESULT)0x8004D502L)

/*
 * MessageId: DRM_E_KEYFILE_CERTIFICATE_CHAIN_NOT_FOUND
 *
 * MessageText:
 *
 * The certificate chain requested was not found in the keyfile.
 *
 */
#define DRM_E_KEYFILE_CERTIFICATE_CHAIN_NOT_FOUND ((DRM_RESULT)0x8004D503L)

/*
 * MessageId: DRM_E_KEYFILE_KEY_NOT_FOUND
 *
 * MessageText:
 *
 * The AES Key ID was not found in the keyfile.
 *
 */
#define DRM_E_KEYFILE_KEY_NOT_FOUND      ((DRM_RESULT)0x8004D504L)

/*
 * MessageId: DRM_E_KEYFILE_UNKNOWN_DECRYPTION_METHOD
 *
 * MessageText:
 *
 * Unknown keyfile decryption method.
 *
 */
#define DRM_E_KEYFILE_UNKNOWN_DECRYPTION_METHOD ((DRM_RESULT)0x8004D505L)

/*
 * MessageId: DRM_E_KEYFILE_INVALID_SIGNATURE
 *
 * MessageText:
 *
 * The keyfile signature was not valid.
 *
 */
#define DRM_E_KEYFILE_INVALID_SIGNATURE  ((DRM_RESULT)0x8004D506L)

/*
 * MessageId: DRM_E_KEYFILE_INTERNAL_DECRYPTION_BUFFER_TOO_SMALL
 *
 * MessageText:
 *
 * The internal decryption buffer is too small to hold the encrypted key from the keyfile.
 *
 */
#define DRM_E_KEYFILE_INTERNAL_DECRYPTION_BUFFER_TOO_SMALL ((DRM_RESULT)0x8004D507L)

/*
 * MessageId: DRM_E_KEYFILE_PLATFORMID_MISMATCH
 *
 * MessageText:
 *
 * Platform ID in the certificate does not match expected value.
 *
 */
#define DRM_E_KEYFILE_PLATFORMID_MISMATCH ((DRM_RESULT)0x8004D508L)

/*
 * MessageId: DRM_E_KEYFILE_CERTIFICATE_ISSUER_KEY_MISMATCH
 *
 * MessageText:
 *
 * Issuer key of the device certificate does not match public key of the model certificate.
 *
 */
#define DRM_E_KEYFILE_CERTIFICATE_ISSUER_KEY_MISMATCH ((DRM_RESULT)0x8004D509L)

/*
 * MessageId: DRM_E_KEYFILE_ROBUSTNESSVERSION_MISMATCH
 *
 * MessageText:
 *
 * Robustness version in the certificate does not match expected value.
 *
 */
#define DRM_E_KEYFILE_ROBUSTNESSVERSION_MISMATCH ((DRM_RESULT)0x8004D50AL)

/*
 * MessageId: DRM_E_KEYFILE_FILE_NOT_CLOSED
 *
 * MessageText:
 *
 * The KeyFile Close function was not called before trying to unintialize the KeyFile context.
 *
 */
#define DRM_E_KEYFILE_FILE_NOT_CLOSED    ((DRM_RESULT)0x8004D50BL)

/*
 * MessageId: DRM_E_KEYFILE_NOT_INITED
 *
 * MessageText:
 *
 * The KeyFile Context was not initialized before trying to use it.
 *
 */
#define DRM_E_KEYFILE_NOT_INITED         ((DRM_RESULT)0x8004D50CL)

/*
 * MessageId: DRM_E_KEYFILE_FORMAT_INVALID
 *
 * MessageText:
 *
 * The format of the KeyFile was invalid.
 *
 */
#define DRM_E_KEYFILE_FORMAT_INVALID     ((DRM_RESULT)0x8004D50DL)

/*
 * MessageId: DRM_E_KEYFILE_UPDATE_NOT_ALLOWED
 *
 * MessageText:
 *
 * The keyfile of the device is read only, and updates are not permitted.
 *
 */
#define DRM_E_KEYFILE_UPDATE_NOT_ALLOWED ((DRM_RESULT)0x8004D50EL)


/* ------------------------------------------------------------
** DRM_E_BASECODE + 0x1600 - DRM_E_BASECODE + 0x16ff (0x8004d600-0x8004d6ff)
** are reserved for additional DRM Services error codes.
**
** See source\common\services\inc\svcerrors.h for Services error codes.
**
** ------------------------------------------------------------
*/

#define DRM_E_SERVICES_BASECODE_EX     (DRM_E_BASECODE + 0x1600)

/* ------------------------------------------------------------
**
** PRND errors: error codes from DRM_E_BASECODE + 0x1700 to
** DRM_E_BASECODE + 0x177f, 0x8004d700-0x8004d77f.
**
** ------------------------------------------------------------
*/

#define DRM_E_PRND_BASECODE			(DRM_E_BASECODE + 0x1700)

/*
 * MessageId: DRM_E_PRND_MESSAGE_VERSION_INVALID
 *
 * MessageText:
 *
 * The PRND message version is not supported.
 *
 */
#define DRM_E_PRND_MESSAGE_VERSION_INVALID ((DRM_RESULT)0x8004D700L)

/*
 * MessageId: DRM_E_PRND_MESSAGE_WRONG_TYPE
 *
 * MessageText:
 *
 * This method does not processs this PRND message type.
 *
 */
#define DRM_E_PRND_MESSAGE_WRONG_TYPE    ((DRM_RESULT)0x8004D701L)

/*
 * MessageId: DRM_E_PRND_MESSAGE_INVALID
 *
 * MessageText:
 *
 * The PRND message does not conform to the PRND spec and is therefore invalid.
 *
 */
#define DRM_E_PRND_MESSAGE_INVALID       ((DRM_RESULT)0x8004D702L)

/*
 * MessageId: DRM_E_PRND_SESSION_ID_INVALID
 *
 * MessageText:
 *
 * The PRND message has a different Session ID than the one used in the PRND Registration Response Message and is therefore invalid.
 * The Receiver is unable to generate a renewal Registration Request Message using a different session.  Use the session matching the previous session ID.
 * The Transmitter is unable to process a renewal Registration Request Message using a different session.  Use the session matching the previous session ID.
 *
 */
#define DRM_E_PRND_SESSION_ID_INVALID    ((DRM_RESULT)0x8004D703L)

/*
 * MessageId: DRM_E_PRND_PROXIMITY_DETECTION_REQUEST_CHANNEL_TYPE_UNSUPPORTED
 *
 * MessageText:
 *
 * The PRND Registration Request Message indicated that it only supports Proximity Detection Channel Types that the Transmitter does not support.
 *
 */
#define DRM_E_PRND_PROXIMITY_DETECTION_REQUEST_CHANNEL_TYPE_UNSUPPORTED ((DRM_RESULT)0x8004D704L)

/*
 * MessageId: DRM_E_PRND_PROXIMITY_DETECTION_RESPONSE_INVALID
 *
 * MessageText:
 *
 * The PRND Proximity Detection Response Message was successfully parsed but the nonce is invalid.
 *
 */
#define DRM_E_PRND_PROXIMITY_DETECTION_RESPONSE_INVALID ((DRM_RESULT)0x8004D705L)

/*
 * MessageId: DRM_E_PRND_PROXIMITY_DETECTION_RESPONSE_TIMEOUT
 *
 * MessageText:
 *
 * The PRND Proximity Detection Response Message was successfully processed but did not arrive in time to verify that the Receiver is Near the Transmitter.
 *
 */
#define DRM_E_PRND_PROXIMITY_DETECTION_RESPONSE_TIMEOUT ((DRM_RESULT)0x8004D706L)

/*
 * MessageId: DRM_E_PRND_LICENSE_REQUEST_CID_CALLBACK_REQUIRED
 *
 * MessageText:
 *
 * The PRND License Request Message used Content Identifier Type Custom.  A Content Identifier Callback to convert the value to a KID is required.
 *
 */
#define DRM_E_PRND_LICENSE_REQUEST_CID_CALLBACK_REQUIRED ((DRM_RESULT)0x8004D707L)

/*
 * MessageId: DRM_E_PRND_LICENSE_RESPONSE_CLMID_INVALID
 *
 * MessageText:
 *
 * The PRND License Response Message had an invalid Current License Message ID.
 *
 */
#define DRM_E_PRND_LICENSE_RESPONSE_CLMID_INVALID ((DRM_RESULT)0x8004D708L)

/*
 * MessageId: DRM_E_PRND_CERTIFICATE_NOT_RECEIVER
 *
 * MessageText:
 *
 * The PRND Registration Request Message did not include a PlayReady certificate that supports the RECEIVER feature.
 *
 */
#define DRM_E_PRND_CERTIFICATE_NOT_RECEIVER ((DRM_RESULT)0x8004D709L)

/*
 * MessageId: DRM_E_PRND_CANNOT_RENEW_USING_NEW_SESSION
 *
 * MessageText:
 *
 * The Transmitter is unable to process a renewal Registration Request Message using a new session.  Use the existing session.
 * The Receiver is unable to generate a renewal Registration Request Message using a new session.  Use the existing session.
 *
 */
#define DRM_E_PRND_CANNOT_RENEW_USING_NEW_SESSION ((DRM_RESULT)0x8004D70AL)

/*
 * MessageId: DRM_E_PRND_INVALID_CUSTOM_DATA_TYPE
 *
 * MessageText:
 *
 * The Custom Data type is invalid. The first four bytes of Custom Data Type ID cannot be 0x4d534654 ( MSFT in ascii ).
 *
 */
#define DRM_E_PRND_INVALID_CUSTOM_DATA_TYPE ((DRM_RESULT)0x8004D70BL)

/*
 * MessageId: DRM_E_PRND_CLOCK_OUT_OF_SYNC
 *
 * MessageText:
 *
 * The clock on the Receiver is not synchronized with the clock on the Transmitter.  Synchronize the clocks.
 *
 */
#define DRM_E_PRND_CLOCK_OUT_OF_SYNC     ((DRM_RESULT)0x8004D70CL)

/*
 * MessageId: DRM_E_PRND_CANNOT_REBIND_PRND_RECEIVED_LICENSE
 *
 * MessageText:
 *
 * The license cannot be rebound to the PRND Receiver because it was itself received from a PRND Transmitter.
 *
 */
#define DRM_E_PRND_CANNOT_REBIND_PRND_RECEIVED_LICENSE ((DRM_RESULT)0x8004D70DL)

/*
 * MessageId: DRM_E_PRND_CANNOT_REGISTER_USING_EXISTING_SESSION
 *
 * MessageText:
 *
 * The Receiver is unable to generate a non-renewal Registration Request Message using an existing session.  End the existing session first or use a new session.
 *
 */
#define DRM_E_PRND_CANNOT_REGISTER_USING_EXISTING_SESSION ((DRM_RESULT)0x8004D70EL)

/*
 * MessageId: DRM_E_PRND_BUSY_PERFORMING_RENEWAL
 *
 * MessageText:
 *
 * The Receiver is currently unable to process a message of this type because it is in the middle of renewing the session.
 *
 */
#define DRM_E_PRND_BUSY_PERFORMING_RENEWAL ((DRM_RESULT)0x8004D70FL)

/*
 * MessageId: DRM_E_PRND_LICENSE_REQUEST_INVALID_ACTION
 *
 * MessageText:
 *
 * Play with no qualifier during license request is all that's supported in v1 of the PRND protocol.
 *
 */
#define DRM_E_PRND_LICENSE_REQUEST_INVALID_ACTION ((DRM_RESULT)0x8004D710L)

/*
 * MessageId: DRM_E_PRND_TRANSMITTER_UNAUTHORIZED
 *
 * MessageText:
 *
 * The Transmitter attempted to authorize with the Receiver but was unsuccessful.
 *
 */
#define DRM_E_PRND_TRANSMITTER_UNAUTHORIZED ((DRM_RESULT)0x8004D711L)


/* ------------------------------------------------------------
**
** OEMHAL errors: error codes from DRM_E_BASECODE + 0x1780 to
** DRM_E_BASECODE + 0x17ff, 0x8004d780-0x8004d7ff.
**
** ------------------------------------------------------------
*/

#define DRM_E_OEMHAL_BASECODE      (DRM_E_BASECODE + 0x1780)

/*
 * MessageId: DRM_E_OEMHAL_NOT_INITIALIZED
 *
 * MessageText:
 *
 * The OEM HAL is not initialized.
 *
 */
#define DRM_E_OEMHAL_NOT_INITIALIZED     ((DRM_RESULT)0x8004D780L)

/*
 * MessageId: DRM_E_OEMHAL_OUT_OF_KEY_REGISTERS
 *
 * MessageText:
 *
 * There are no more key registers available in the OEM HAL implementation.
 *
 */
#define DRM_E_OEMHAL_OUT_OF_KEY_REGISTERS ((DRM_RESULT)0x8004D781L)

/*
 * MessageId: DRM_E_OEMHAL_KEYS_IN_USE
 *
 * MessageText:
 *
 * The OEM HAL is being shutdown whilst keys are still allocated.
 *
 */
#define DRM_E_OEMHAL_KEYS_IN_USE         ((DRM_RESULT)0x8004D782L)

/*
 * MessageId: DRM_E_OEMHAL_NO_KEY
 *
 * MessageText:
 *
 * The requested preloaded key is not available or the key handle is otherwise invalid.
 *
 */
#define DRM_E_OEMHAL_NO_KEY              ((DRM_RESULT)0x8004D783L)

/*
 * MessageId: DRM_E_OEMHAL_UNSUPPORTED_KEY_TYPE
 *
 * MessageText:
 *
 * The specified key type cannot be used for the operation requested.
 *
 */
#define DRM_E_OEMHAL_UNSUPPORTED_KEY_TYPE ((DRM_RESULT)0x8004D784L)

/*
 * MessageId: DRM_E_OEMHAL_UNSUPPORTED_KEY_WRAPPING_FORMAT
 *
 * MessageText:
 *
 * The specified wrapping key type cannot be used to unwrap the specified key.
 *
 */
#define DRM_E_OEMHAL_UNSUPPORTED_KEY_WRAPPING_FORMAT ((DRM_RESULT)0x8004D785L)

/*
 * MessageId: DRM_E_OEMHAL_UNSUPPORTED_KEY_LENGTH
 *
 * MessageText:
 *
 * The key buffer provided is of the wrong length for the specified key/wrapping key combination.
 *
 */
#define DRM_E_OEMHAL_UNSUPPORTED_KEY_LENGTH ((DRM_RESULT)0x8004D786L)

/*
 * MessageId: DRM_E_OEMHAL_UNSUPPORTED_HASH_TYPE
 *
 * MessageText:
 *
 * The specified hash type is not supported.
 *
 */
#define DRM_E_OEMHAL_UNSUPPORTED_HASH_TYPE ((DRM_RESULT)0x8004D787L)

/*
 * MessageId: DRM_E_OEMHAL_UNSUPPORTED_SIGNATURE_SCHEME
 *
 * MessageText:
 *
 * The specified signature scheme is not supported.
 *
 */
#define DRM_E_OEMHAL_UNSUPPORTED_SIGNATURE_SCHEME ((DRM_RESULT)0x8004D788L)

/*
 * MessageId: DRM_E_OEMHAL_BUFFER_TOO_LARGE
 *
 * MessageText:
 *
 * The output buffer is larger than the input buffer and must be the same size.
 *
 */
#define DRM_E_OEMHAL_BUFFER_TOO_LARGE    ((DRM_RESULT)0x8004D789L)

/*
 * MessageId: DRM_E_OEMHAL_SAMPLE_ENCRYPTION_MODE_NOT_PERMITTED
 *
 * MessageText:
 *
 * The sample encryption mode is not permitted for this combination of encrypt parameters.
 *
 */
#define DRM_E_OEMHAL_SAMPLE_ENCRYPTION_MODE_NOT_PERMITTED ((DRM_RESULT)0x8004D78AL)



/* ------------------------------------------------------------
**
** MPEG2 TS Encryptor errors: error codes from DRM_E_BASECODE+0x1800 to
** DRM_E_BASECODE+0x18FF, 0x8004d800-0x8004d8ff.
**
** ------------------------------------------------------------
*/
#define DRM_E_M2TS_BASECODE                    (DRM_E_BASECODE + 0x1800)

/*
 * MessageId: DRM_E_M2TS_PAT_PID_IS_NOT_ZERO
 *
 * MessageText:
 *
 * PID 0 is reserved for PAT and cannot be used for other type of packet.
 *
 */
#define DRM_E_M2TS_PAT_PID_IS_NOT_ZERO   ((DRM_RESULT)0x8004D800L)

/*
 * MessageId: DRM_E_M2TS_PTS_NOT_EXIST
 *
 * MessageText:
 *
 * The audio/video PES doesn' have the PTS data.
 *
 */
#define DRM_E_M2TS_PTS_NOT_EXIST         ((DRM_RESULT)0x8004D801L)

/*
 * MessageId: DRM_E_M2TS_PES_PACKET_LENGTH_NOT_SPECIFIED
 *
 * MessageText:
 *
 * The audio PES' packet length is 0 which is not allowed.
 *
 */
#define DRM_E_M2TS_PES_PACKET_LENGTH_NOT_SPECIFIED ((DRM_RESULT)0x8004D802L)

/*
 * MessageId: DRM_E_M2TS_OUTPUT_BUFFER_FULL
 *
 * MessageText:
 *
 * The output buffer for receiving the encrypted packets is full.
 *
 */
#define DRM_E_M2TS_OUTPUT_BUFFER_FULL    ((DRM_RESULT)0x8004D803L)

/*
 * MessageId: DRM_E_M2TS_CONTEXT_NOT_INITIALIZED
 *
 * MessageText:
 *
 * The encryptor context hasn't been initialized yet.
 *
 */
#define DRM_E_M2TS_CONTEXT_NOT_INITIALIZED ((DRM_RESULT)0x8004D804L)

/*
 * MessageId: DRM_E_M2TS_NEED_KEY_DATA
 *
 * MessageText:
 *
 * The key data for encrypting the sample is either hasn't been set or the encryptor needs next key due to key rotation.
 *
 */
#define DRM_E_M2TS_NEED_KEY_DATA         ((DRM_RESULT)0x8004D805L)

/*
 * MessageId: DRM_E_M2TS_DDPLUS_FORMAT_INVALID
 *
 * MessageText:
 *
 * Not supported DDPlus format.
 *
 */
#define DRM_E_M2TS_DDPLUS_FORMAT_INVALID ((DRM_RESULT)0x8004D806L)

/*
 * MessageId: DRM_E_M2TS_NOT_UNIT_START_PACKET
 *
 * MessageText:
 *
 * The encryptor expects a unit start packet.  The unit start packet should appear before the rest of the packets in the unit. 
 *
 */
#define DRM_E_M2TS_NOT_UNIT_START_PACKET ((DRM_RESULT)0x8004D807L)

/*
 * MessageId: DRM_E_M2TS_TOO_MANY_SUBSAMPLES
 *
 * MessageText:
 *
 * Too many subsamples over the limit that the ECM allows.
 *
 */
#define DRM_E_M2TS_TOO_MANY_SUBSAMPLES   ((DRM_RESULT)0x8004D808L)

/*
 * MessageId: DRM_E_M2TS_TABLE_ID_INVALID
 *
 * MessageText:
 *
 * The PAT or PMT packet contains an invalid table ID.
 *
 */
#define DRM_E_M2TS_TABLE_ID_INVALID      ((DRM_RESULT)0x8004D809L)

/*
 * MessageId: DRM_E_M2TS_PACKET_SYNC_BYTE_INVALID
 *
 * MessageText:
 *
 * The TS packet doesn't start with the 0x47 (sync byte).
 *
 */
#define DRM_E_M2TS_PACKET_SYNC_BYTE_INVALID ((DRM_RESULT)0x8004D80AL)

/*
 * MessageId: DRM_E_M2TS_ADAPTATION_LENGTH_INVALID
 *
 * MessageText:
 *
 * The adaptation field length is invalid.
 *
 */
#define DRM_E_M2TS_ADAPTATION_LENGTH_INVALID ((DRM_RESULT)0x8004D80BL)

/*
 * MessageId: DRM_E_M2TS_PAT_HEADER_INVALID
 *
 * MessageText:
 *
 * There is an error in PAT header, unable to parse it.
 *
 */
#define DRM_E_M2TS_PAT_HEADER_INVALID    ((DRM_RESULT)0x8004D80CL)

/*
 * MessageId: DRM_E_M2TS_PMT_HEADER_INVALID
 *
 * MessageText:
 *
 * There is an error in PMT header, unable to parse it.
 *
 */
#define DRM_E_M2TS_PMT_HEADER_INVALID    ((DRM_RESULT)0x8004D80DL)

/*
 * MessageId: DRM_E_M2TS_PES_START_CODE_NOT_FOUND
 *
 * MessageText:
 *
 * Cannot find the PES start code (0x000001).
 *
 */
#define DRM_E_M2TS_PES_START_CODE_NOT_FOUND ((DRM_RESULT)0x8004D80EL)

/*
 * MessageId: DRM_E_M2TS_STREAM_OR_PACKET_TYPE_CHANGED
 *
 * MessageText:
 *
 * The stream type or packet type of an existing PID has changed 
 *
 */
#define DRM_E_M2TS_STREAM_OR_PACKET_TYPE_CHANGED ((DRM_RESULT)0x8004D80FL)

/*
 * MessageId: DRM_E_M2TS_INTERNAL_ERROR
 *
 * MessageText:
 *
 * An internal error occurred during encryptrion.
 *
 */
#define DRM_E_M2TS_INTERNAL_ERROR        ((DRM_RESULT)0x8004D810L)

/*
 * MessageId: DRM_E_M2TS_ADTS_FORMAT_INVALID
 *
 * MessageText:
 *
 * Not supported ADTS format.
 *
 */
#define DRM_E_M2TS_ADTS_FORMAT_INVALID   ((DRM_RESULT)0x8004D811L)

/*
 * MessageId: DRM_E_M2TS_MPEGA_FORMAT_INVALID
 *
 * MessageText:
 *
 * Not supported MPEGA format.
 *
 */
#define DRM_E_M2TS_MPEGA_FORMAT_INVALID  ((DRM_RESULT)0x8004D812L)

/*
 * MessageId: DRM_E_M2TS_CA_DESCRIPTOR_LENGTH_INVALID
 *
 * MessageText:
 *
 * The CA_descruptor length is greater than ES_info length.
 *
 */
#define DRM_E_M2TS_CA_DESCRIPTOR_LENGTH_INVALID ((DRM_RESULT)0x8004D813L)

/*
 * MessageId: DRM_E_M2TS_CRC_FIELD_INVALID
 *
 * MessageText:
 *
 * The CRC field in the PAT or PMT packet is invalid.
 *
 */
#define DRM_E_M2TS_CRC_FIELD_INVALID     ((DRM_RESULT)0x8004D814L)

/*
 * MessageId: DRM_E_M2TS_INCOMPLETE_SECTION_HEADER
 *
 * MessageText:
 *
 * The section header of a PES is not completed while the next PES packet has started already
 *
 */
#define DRM_E_M2TS_INCOMPLETE_SECTION_HEADER ((DRM_RESULT)0x8004D815L)

/*
 * MessageId: DRM_E_M2TS_INVALID_UNALIGNED_DATA
 *
 * MessageText:
 *
 * Not allowed to have the overflow of the unaligned payload to accross more than one PES
 *
 */
#define DRM_E_M2TS_INVALID_UNALIGNED_DATA ((DRM_RESULT)0x8004D816L)

/*
 * MessageId: DRM_E_M2TS_GET_ENCRYPTED_DATA_FIRST
 *
 * MessageText:
 *
 * Do not pass additional data for encryption when the last encryption result is DRM_S_MORE_DATA
 *
 */
#define DRM_E_M2TS_GET_ENCRYPTED_DATA_FIRST ((DRM_RESULT)0x8004D817L)

/*
 * MessageId: DRM_E_M2TS_CANNOT_CHANGE_PARAMETER
 *
 * MessageText:
 *
 * Not allowed to change the encryption parameter once the encryption started, i.e. after Drm_M2ts_Encrypt is called
 *
 */
#define DRM_E_M2TS_CANNOT_CHANGE_PARAMETER ((DRM_RESULT)0x8004D818L)

/*
 * MessageId: DRM_E_M2TS_UNKNOWN_PACKET
 *
 * MessageText:
 *
 * This packet appears before the first PAT and/or PMT and will be dropped.
 *
 */
#define DRM_E_M2TS_UNKNOWN_PACKET        ((DRM_RESULT)0x8004D819L)

/*
 * MessageId: DRM_E_M2TS_DROP_PACKET
 *
 * MessageText:
 *
 * This packet should be dropped because at least one field in the packet contains an invalid data.
 *
 */
#define DRM_E_M2TS_DROP_PACKET           ((DRM_RESULT)0x8004D820L)

/*
 * MessageId: DRM_E_M2TS_DROP_PES
 *
 * MessageText:
 *
 * This PES packet should be dropped because the PES packet is not valid.
 *
 */
#define DRM_E_M2TS_DROP_PES              ((DRM_RESULT)0x8004D821L)

/*
 * MessageId: DRM_E_M2TS_INCOMPLETE_PES
 *
 * MessageText:
 *
 * This PES packet has one or more missing packets.
 *
 */
#define DRM_E_M2TS_INCOMPLETE_PES        ((DRM_RESULT)0x8004D822L)

/*
 * MessageId: DRM_E_M2TS_WAITED_TOO_LONG
 *
 * MessageText:
 *
 * This packet is dropped because its unit is not completed after a long period of time.
 *
 */
#define DRM_E_M2TS_WAITED_TOO_LONG       ((DRM_RESULT)0x8004D823L)

/*
 * MessageId: DRM_E_M2TS_SECTION_LENGTH_INVALID
 *
 * MessageText:
 *
 * The section length inside the PAT or PMT is less than the minimun PAT or PMT section.
 *
 */
#define DRM_E_M2TS_SECTION_LENGTH_INVALID ((DRM_RESULT)0x8004D824L)

/*
 * MessageId: DRM_E_M2TS_PROGRAM_INFO_LENGTH_INVALID
 *
 * MessageText:
 *
 * The sum of the program info length and the other fields in the PMT section don't match with the section length.
 *
 */
#define DRM_E_M2TS_PROGRAM_INFO_LENGTH_INVALID ((DRM_RESULT)0x8004D825L)

/*
 * MessageId: DRM_E_M2TS_PES_HEADER_INVALID
 *
 * MessageText:
 *
 * Failed to parse the PES header, the PES maybe too short.
 *
 */
#define DRM_E_M2TS_PES_HEADER_INVALID    ((DRM_RESULT)0x8004D826L)

/*
 * MessageId: DRM_E_M2TS_ECM_PAYLOAD_OVER_LIMIT
 *
 * MessageText:
 *
 * The size of the ECM payload exceeds the limit of 64k bytes
 *
 */
#define DRM_E_M2TS_ECM_PAYLOAD_OVER_LIMIT ((DRM_RESULT)0x8004D827L)

/*
 * MessageId: DRM_E_M2TS_SET_CA_PID_FAILED
 *
 * MessageText:
 *
 * Unable to assign a PID for CA_PID, all PIDs in the range of 0x0010 to 0x1FFE are used.
 *
 */
#define DRM_E_M2TS_SET_CA_PID_FAILED     ((DRM_RESULT)0x8004D828L)


/* ------------------------------------------------------------
**
** LicGen errors: error codes from DRM_E_BASECODE + 0x1900 to
** DRM_E_BASECODE + 0x19ff, 0x8004d900-0x8004d9ff.
**
** ------------------------------------------------------------
*/

#define DRM_E_LICGEN_BASECODE			(DRM_E_BASECODE + 0x1900)

/*
 * MessageId: DRM_E_LICGEN_CANNOT_PERSIST_LICENSE
 *
 * MessageText:
 *
 * A non-persistent license cannot be stored in the license store.
 *
 */
#define DRM_E_LICGEN_CANNOT_PERSIST_LICENSE ((DRM_RESULT)0x8004D901L)

/*
 * MessageId: DRM_E_LICGEN_PERSISTENT_REMOTE_LICENSE
 *
 * MessageText:
 *
 * A remote bound license should be non-persistent.
 *
 */
#define DRM_E_LICGEN_PERSISTENT_REMOTE_LICENSE ((DRM_RESULT)0x8004D902L)

/*
 * MessageId: DRM_E_LICGEN_EXPIRE_AFTER_FIRST_PLAY_REMOTE_LICENSE
 *
 * MessageText:
 *
 * A remote bound license should not have expire after first play property.
 *
 */
#define DRM_E_LICGEN_EXPIRE_AFTER_FIRST_PLAY_REMOTE_LICENSE ((DRM_RESULT)0x8004D903L)

/*
 * MessageId: DRM_E_LICGEN_ROOT_LICENSE_CANNOT_ENCRYPT
 *
 * MessageText:
 *
 * A root license should not be used to encrypt content.
 *
 */
#define DRM_E_LICGEN_ROOT_LICENSE_CANNOT_ENCRYPT ((DRM_RESULT)0x8004D904L)

/*
 * MessageId: DRM_E_LICGEN_EMBED_LOCAL_LICENSE
 *
 * MessageText:
 *
 * A local bound license cannot be embedded.
 *
 */
#define DRM_E_LICGEN_EMBED_LOCAL_LICENSE ((DRM_RESULT)0x8004D905L)

/*
 * MessageId: DRM_E_LICGEN_LOCAL_LICENSE_WITH_REMOTE_CERTIFICATE
 *
 * MessageText:
 *
 * A local bound license cannot be bound to a remote certificate. 
 *
 */
#define DRM_E_LICGEN_LOCAL_LICENSE_WITH_REMOTE_CERTIFICATE ((DRM_RESULT)0x8004D906L)

/*
 * MessageId: DRM_E_LICGEN_PLAY_ENABLER_REMOTE_LICENSE
 *
 * MessageText:
 *
 * A remote bound license cannot have play enablers other than Passing to Unknown Output or Passing Constrained Resolution to Unknown Output.
 *
 */
#define DRM_E_LICGEN_PLAY_ENABLER_REMOTE_LICENSE ((DRM_RESULT)0x8004D907L)

/*
 * MessageId: DRM_E_LICGEN_DUPLICATE_PLAY_ENABLER
 *
 * MessageText:
 *
 * A license descriptor contains a duplicate play enabler.
 *
 */
#define DRM_E_LICGEN_DUPLICATE_PLAY_ENABLER ((DRM_RESULT)0x8004D908L)

/* ------------------------------------------------------------
**
** Available range 0x8004da00-0x8004dfff.
**
** ------------------------------------------------------------
*/

/* Insert new PKCore sub-error facilities here */


/* ============================================================
**
** PC specific errors (from 0x8004e000 to 0x8004ffff)
**
** ============================================================
*/

/* Nothing should be added here - PC error codes are found in DrmPcErrors.h */


/* ============================================================
**
** Deprecated errors.  Returned in previous versions of PlayReady but not in the current version.
** Note: No new error codes should be defined with the same values as these.
**
** ============================================================
*/

#define DRM_E_DEPRECATED_CH_UNSUPPORTED_HASH_ALGORITHM                            ((DRM_RESULT)0x8004110CL)
#define DRM_E_DEPRECATED_CH_UNSUPPORTED_SIGN_ALGORITHM                            ((DRM_RESULT)0x8004110DL)
#define DRM_E_DEPRECATED_CH_NOT_SIGNED                                            ((DRM_RESULT)0x80041113L)
#define DRM_E_DEPRECATED_CH_UNKNOWN_ERROR                                         ((DRM_RESULT)0x80041116L)
#define DRM_E_DEPRECATED_LIC_INIT_FAILURE                                         ((DRM_RESULT)0x80041201L)
#define DRM_E_DEPRECATED_LIC_LICENSE_NOTSET                                       ((DRM_RESULT)0x80041202L)
#define DRM_E_DEPRECATED_LIC_MEMORY_ALLOCATION_ERROR                              ((DRM_RESULT)0x80041204L)
#define DRM_E_DEPRECATED_LIC_FIELD_MISSING                                        ((DRM_RESULT)0x80041206L)
#define DRM_E_DEPRECATED_LIC_UNKNOWN_ERROR                                        ((DRM_RESULT)0x80041208L)
#define DRM_E_DEPRECATED_LIC_INVALID_REVLIST                                      ((DRM_RESULT)0x80041209L)
#define DRM_E_DEPRECATED_LIC_EXPIRED_CERT                                         ((DRM_RESULT)0x8004120AL)
#define DRM_E_DEPRECATED_CPRMEXP_PARAM_NOT_OPTIONAL                               ((DRM_RESULT)0x80041401L)
#define DRM_E_DEPRECATED_CPRMEXP_MEMORY_ALLOCATION_ERROR                          ((DRM_RESULT)0x80041402L)
#define DRM_E_DEPRECATED_CPRMEXP_ENDOFBUFFER                                      ((DRM_RESULT)0x8004140AL)
#define DRM_E_DEPRECATED_LIC_KEY_AND_CERT_MISMATCH                                ((DRM_RESULT)0x80048013L)
#define DRM_E_DEPRECATED_STACK_TOO_SMALL                                          ((DRM_RESULT)0x800480D1L)
#define DRM_E_DEPRECATED_CONTRACT_FAILED                                          ((DRM_RESULT)0x8004A006L)
#define DRM_E_DEPRECATED_NO_LICENSES_TO_SYNC                                      ((DRM_RESULT)0x8004A017L)
#define DRM_E_DEPRECATED_INCOMPATABLE_LICENSE_SIZE                                ((DRM_RESULT)0x8004C004L)
#define DRM_E_DEPRECATED_INVALID_LICENSE_FLAGS                                    ((DRM_RESULT)0x8004C005L)
#define DRM_E_DEPRECATED_CONDITION_FAIL                                           ((DRM_RESULT)0x8004C007L)
#define DRM_E_DEPRECATED_LICENSE_NOT_YET_VALID                                    ((DRM_RESULT)0x8004C00AL)
#define DRM_E_DEPRECATED_NO_RIGHTS_REQUESTED                                      ((DRM_RESULT)0x8004C00EL)
#define DRM_E_DEPRECATED_INVALID_TIME                                             ((DRM_RESULT)0x8004C011L)
#define DRM_E_DEPRECATED_INVALID_BIND_ID                                          ((DRM_RESULT)0x8004C015L)
#define DRM_E_DEPRECATED_ALGORITHM_NOT_SET                                        ((DRM_RESULT)0x8004C017L)
#define DRM_E_DEPRECATED_LICENSE_SERVER_NEEDS_KEY                                 ((DRM_RESULT)0x8004C018L)
#define DRM_E_DEPRECATED_CLIENT_TIME_INVALID                                      ((DRM_RESULT)0x8004C01CL)
#define DRM_E_DEPRECATED_DST_NAMESPACE_FULL                                       ((DRM_RESULT)0x8004C022L)
#define DRM_E_DEPRECATED_DST_NAMESPACE_IN_USE                                     ((DRM_RESULT)0x8004C028L)
#define DRM_E_DEPRECATED_NO_ACTION_IN_LICENSE_REQUEST                             ((DRM_RESULT)0x8004C02CL)
#define DRM_E_DEPRECATED_BACKUP_EXISTS                                            ((DRM_RESULT)0x8004C032L)
#define DRM_E_DEPRECATED_DST_RESERVED_KEY_DETECTED                                ((DRM_RESULT)0x8004C03AL)
#define DRM_E_DEPRECATED_CLK_UNSUPPORTED_VALUE                                    ((DRM_RESULT)0x8004C041L)
#define DRM_E_DEPRECATED_DEVCERT_TEMPLATE_EXCEEDS_SIZE_LIMIT                      ((DRM_RESULT)0x8004C044L)
#define DRM_E_DEPRECATED_DEVCERT_WRITE_ERROR                                      ((DRM_RESULT)0x8004C046L)
#define DRM_E_DEPRECATED_PRIVKEY_WRITE_ERROR                                      ((DRM_RESULT)0x8004C048L)
#define DRM_E_DEPRECATED_DEVCERT_INDIV_NOT_SUPPORTED                              ((DRM_RESULT)0x8004C04BL)
#define DRM_E_DEPRECATED_WRONG_TOKEN_TYPE                                         ((DRM_RESULT)0x8004C058L)
#define DRM_E_DEPRECATED_POLICY_ONLINE_DISABLED                                   ((DRM_RESULT)0x8004C05AL)
#define DRM_E_DEPRECATED_PRECISION_ARITHMETIC_FAIL                                ((DRM_RESULT)0x8004C06CL)
#define DRM_E_DEPRECATED_REVOCATION_NOT_SUPPORTED                                 ((DRM_RESULT)0x8004C071L)
#define DRM_E_DEPRECATED_LRB_NO_LGPUBKEY                                          ((DRM_RESULT)0x8004C0A0L)
#define DRM_E_DEPRECATED_LRB_INVALID_SIGNATURE                                    ((DRM_RESULT)0x8004C0A1L)
#define DRM_E_DEPRECATED_LRB_LGPUBKEY_MISMATCH                                    ((DRM_RESULT)0x8004C0A2L)
#define DRM_E_DEPRECATED_LRB_INVALID_LICENSE_DATA                                 ((DRM_RESULT)0x8004C0A3L)
#define DRM_E_DEPRECATED_NOT_CRL_BLOB                                             ((DRM_RESULT)0x8004C100L)
#define DRM_E_DEPRECATED_BAD_CRL_BLOB                                             ((DRM_RESULT)0x8004C101L)
#define DRM_E_DEPRECATED_FEATURE_NOT_SUPPORTED                                    ((DRM_RESULT)0x8004C3F4L)
#define DRM_E_DEPRECATED_BCERT_CLIENT_ID_NOT_SPECIFIED                            ((DRM_RESULT)0x8004C810L)
#define DRM_E_DEPRECATED_BCERT_HARDWARE_ID_NOT_SPECIFIED                          ((DRM_RESULT)0x8004C813L)
#define DRM_E_DEPRECATED_BCERT_SERIAL_NUM_NOT_SPECIFIED                           ((DRM_RESULT)0x8004C815L)
#define DRM_E_DEPRECATED_BCERT_INVALID_EXTDATA_SIGNED_LENGTH                      ((DRM_RESULT)0x8004C830L)
#define DRM_E_DEPRECATED_BCERT_INVALID_EXTDATA_RECORD_TYPE                        ((DRM_RESULT)0x8004C831L)
#define DRM_E_DEPRECATED_SECURE_TRACE_BAD_GLOBAL_DATA_POINTER                     ((DRM_RESULT)0x8004CD00L)
#define DRM_E_DEPRECATED_SECURE_TRACE_INVALID_GLOBAL_DATA                         ((DRM_RESULT)0x8004CD01L)
#define DRM_E_DEPRECATED_SECURE_TRACE_FORMATTING_ERROR                            ((DRM_RESULT)0x8004CD02L)
#define DRM_E_DEPRECATED_SECURE_TRACE_BAD_SCHEME_DATA_POINTER                     ((DRM_RESULT)0x8004CD03L)
#define DRM_E_DEPRECATED_SECURE_TRACE_BAD_PER_THREAD_AES_DATA_POINTER             ((DRM_RESULT)0x8004CD04L)
#define DRM_E_DEPRECATED_SECURE_TRACE_BAD_PER_THREAD_AES_BUFFER_POINTER           ((DRM_RESULT)0x8004CD05L)
#define DRM_E_DEPRECATED_SECURE_TRACE_AES_INSUFFICIENT_BUFFER                     ((DRM_RESULT)0x8004CD06L)
#define DRM_E_DEPRECATED_SECURE_TRACE_VERSION_MISMATCH                            ((DRM_RESULT)0x8004CD07L)
#define DRM_E_DEPRECATED_SECURE_TRACE_UNEXPECTED_ERROR                            ((DRM_RESULT)0x8004CD08L)
#define DRM_E_DEPRECATED_ASF_AES_PAYLOAD_FOUND                                    ((DRM_RESULT)0x8004CF05L)
#define DRM_E_DEPRECATED_LICGEN_POLICY_NOT_SUPPORTED                              ((DRM_RESULT)0x8004D100L)
#define DRM_E_DEPRECATED_MOVE_TXID_MISMATCH                                       ((DRM_RESULT)0x8004D303L)

#endif /*__DRMRESULTS_H__ */

