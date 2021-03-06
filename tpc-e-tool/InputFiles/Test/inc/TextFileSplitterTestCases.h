#ifndef TEXT_FILE_SPLITTER_TEST_CASES_H
#define TEXT_FILE_SPLITTER_TEST_CASES_H

/*
 * Legal Notice
 *
 * This document and associated source code (the "Work") is a part of a
 * benchmark specification maintained by the TPC.
 *
 * The TPC reserves all right, title, and interest to the Work as provided
 * under U.S. and international laws, including without limitation all patent
 * and trademark rights therein.
 *
 * No Warranty
 *
 * 1.1 TO THE MAXIMUM EXTENT PERMITTED BY APPLICABLE LAW, THE INFORMATION
 *     CONTAINED HEREIN IS PROVIDED "AS IS" AND WITH ALL FAULTS, AND THE
 *     AUTHORS AND DEVELOPERS OF THE WORK HEREBY DISCLAIM ALL OTHER
 *     WARRANTIES AND CONDITIONS, EITHER EXPRESS, IMPLIED OR STATUTORY,
 *     INCLUDING, BUT NOT LIMITED TO, ANY (IF ANY) IMPLIED WARRANTIES,
 *     DUTIES OR CONDITIONS OF MERCHANTABILITY, OF FITNESS FOR A PARTICULAR
 *     PURPOSE, OF ACCURACY OR COMPLETENESS OF RESPONSES, OF RESULTS, OF
 *     WORKMANLIKE EFFORT, OF LACK OF VIRUSES, AND OF LACK OF NEGLIGENCE.
 *     ALSO, THERE IS NO WARRANTY OR CONDITION OF TITLE, QUIET ENJOYMENT,
 *     QUIET POSSESSION, CORRESPONDENCE TO DESCRIPTION OR NON-INFRINGEMENT
 *     WITH REGARD TO THE WORK.
 * 1.2 IN NO EVENT WILL ANY AUTHOR OR DEVELOPER OF THE WORK BE LIABLE TO
 *     ANY OTHER PARTY FOR ANY DAMAGES, INCLUDING BUT NOT LIMITED TO THE
 *     COST OF PROCURING SUBSTITUTE GOODS OR SERVICES, LOST PROFITS, LOSS
 *     OF USE, LOSS OF DATA, OR ANY INCIDENTAL, CONSEQUENTIAL, DIRECT,
 *     INDIRECT, OR SPECIAL DAMAGES WHETHER UNDER CONTRACT, TORT, WARRANTY,
 *     OR OTHERWISE, ARISING IN ANY WAY OUT OF THIS OR ANY OTHER AGREEMENT
 *     RELATING TO THE WORK, WHETHER OR NOT SUCH AUTHOR OR DEVELOPER HAD
 *     ADVANCE NOTICE OF THE POSSIBILITY OF SUCH DAMAGES.
 *
 * Contributors
 * - Doug Johnson
 */

#include <boost/test/unit_test.hpp>

#include <string>
#include <istream>

#include "../../inc/TextFileSplitter.h"

namespace EGenInputFilesTest
{

    class TextFileSplitterTestCases
    {
    private:
        std::string defaultTestFile;
        std::string mixedTestFile;
        std::string customTestFile;
        std::string emptyTestFile;

        ///////////////////////////////////////////////////////////////////////
        //
        // Used for on-the-fly construction of the tested objects
        //
        TPCE::TextFileSplitter* splitter1;
        //
        ///////////////////////////////////////////////////////////////////////

    public:
        //
        // Constructor / Destructor
        //
        TextFileSplitterTestCases();
        ~TextFileSplitterTestCases();

        //
        // Add test cases to the test suite.
        //
        void AddTestCases( boost::unit_test::test_suite* testSuite, boost::shared_ptr<TextFileSplitterTestCases> tester ) const;


        ///////////////////////////////////////////////////////////////////////
        //
        // This section contains all test case declarations.
        //

        //
        // Constructor test cases
        //
        void TestCase_Constructor_Default();

        void TestCase_eof();
        void TestCase_getNextRecord();

        //
        // End of section containing all test case declarations.
        //
        ///////////////////////////////////////////////////////////////////////
    };

} // namespace EGenInputFilesTest

#endif // TEXT_FILE_SPLITTER_TEST_CASES_H
