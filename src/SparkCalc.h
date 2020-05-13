#ifndef __SparkCalc__
#define __SparkCalc__

/**
@file
Subclass of Spark, which is generated by wxFormBuilder.
*/

#include "wx/wxprec.h"
#include "SparkUI.h"
#include "wx/wxprec.h"
#import "operation-tree/OperationTree.hpp"
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

//// end generated include

/** Implementing Spark */
class SparkCalc : public Spark
{
	public:
		/** Constructor */
		SparkCalc( wxWindow* parent );
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void math_input_evt(wxCommandEvent& event);

    private:
        wxDECLARE_EVENT_TABLE();
};

enum
{
    // menu items
    Spark_Quit = wxID_EXIT,

    // it is important for the id corresponding to the "About" command to have
    // this standard value as otherwise it won't be handled properly under Mac
    // (where it is special and put into the "Apple" menu)
    Spark_About = wxID_ABOUT
};

#endif // __SparkCalc__
