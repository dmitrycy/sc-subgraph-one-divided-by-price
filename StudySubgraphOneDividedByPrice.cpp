// Make sure your custom studies source code file has the following two lines at the top of the file and in this order.

// This must be exactly "sierrachart.h" to ensure you are referencing the correct header file.
#include "sierrachart.h"

// Change the text within the quote marks to what you want to name your group of custom studies.
SCDLLName("Study Subgraph 1 Divided by Price")

// This is the basic framework of a study function.
SCSFExport scsf_StudySubgraph1DividedByPrice(SCStudyInterfaceRef sc)
{
	// Get a reference to the subgraph where we will plot the inverse.
	SCSubgraphRef Subgraph_Inverse = sc.Subgraph[0];

	// Get a reference to the study we want to invert.
	SCInputRef Input_Study = sc.Input[0];

	// These are just more convenient names to refer to a study's input data and its output subgraph.

	// Set the configuration and defaults.
	if (sc.SetDefaults)
	{
		// Give the study an initial name.
		sc.GraphName = "Study Subgraph 1 Divided by Price";

		// This is the input name that will show up in the study settings menu.
		Input_Study.Name = "Input Data";

		// Gives you the input menu to select another study as input in the study settings menu.
		Input_Study.SetStudySubgraphValues(0, 0);

		// Get the name of the subgraph we are plotting from the study
		SCString StudySubgraphName = sc.GetStudySubgraphName(Input_Study.GetStudyID(), Input_Study.GetSubgraphIndex());

		// This creates a subgraph in Studies >> Settings >> Subgraphs menu, and is used to display your data.
		Subgraph_Inverse.Name = StudySubgraphName.GetChars();
		Subgraph_Inverse.DrawStyle = DRAWSTYLE_LINE;
		Subgraph_Inverse.PrimaryColor = RGB(0, 255, 0);

		// Allows us to use sc.Index to loop over data.
		sc.AutoLoop = 1;
		return;
	}

	// Update the chart name to reflect the study it is inverting.
	SCString ChartName = sc.GetStudyNameUsingID(Input_Study.GetStudyID());
	sc.GraphName.Format("1 / %s", ChartName.GetChars());

	// Update the subgraph name to reflect the study subgraph it is inverting.
	SCString StudySubgraphName = sc.GetStudySubgraphName(Input_Study.GetStudyID(), Input_Study.GetSubgraphIndex());
	Subgraph_Inverse.Name = StudySubgraphName.GetChars();

	// Get the data from the study.
	SCFloatArray StudyData;
	sc.GetStudyArrayUsingID(Input_Study.GetStudyID(), Input_Study.GetSubgraphIndex(), StudyData);

	// To avoid dividing by zero, check for zero values first.
	if (StudyData[sc.Index] == 0.0f)
		// Manually assign a zero value if zero is found.
		Subgraph_Inverse[sc.Index] == 0.0f;
	else
		// Otherwise perform inversion.
		Subgraph_Inverse[sc.Index] = 1.0f / StudyData[sc.Index];
}
