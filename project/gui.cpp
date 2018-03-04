#include <QApplication>
#include <QPushButton>
#include <QRadioButton>
#include <QCheckBox>

//! Defines the main gui window for all modes
/*!
	The class contains the whole GUI Application.
	<br>It contains a radio button to select between 2D-3D or 3D-2D.
	<br>It contains a check box to check if isometric projection is required.
	<br>It contains a button to upload the file (2D- 3 files needed) or (3D- 1 file).
	<br>It contains one button to start computation.
*/
class mainWindow
{
public:
  	//! A constructor of the main GUI.
    /*!
      Constructs the GUI window of the application. Sets the default positions for radio buttons. Disables the ok button
      in case files have not been uploaded.
    */
	mainWindow();
	//! A destructor of the main GUI.
    /*!
      Closes the window after completion.
    */
	~mainWindow();
	//! Holder of the application
	QApplication app;
	//! Radio button for selecting mode
    /*!
      Two modes - 2D to 3D & 3D to 2D. Defaults to 2D - 3D.
    */
	QRadioButton mode_rb;
	//! Checkbox for selecting if isometric projection is required.
	QCheckBox isometric_cb;
	//! Button to start computation.
	QPushButton ok_but;
};