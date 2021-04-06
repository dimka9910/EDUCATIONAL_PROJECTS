#ifndef GLOBAL
#define GLOBAL
#endif // GLOBAL

/*
 * .probe FILE STRUCTURE
 *
 * qint16             Number of groups
 * {
 * qint8              Origin
 * QString            Group Name
 * QString            Source File Name
 * QString            Source File Path
 * QString            Source File Type
 * QString            Computer name create
 * QString            User name create
 * QDate              Date create
 * QTime              Time create
 * QString            Computer name modify
 * QString            User name modify
 * QDate              Date modify
 * QTime              Time modify
 * qint16             Number of records
 * {
 * QString            Record name
 * }x Number of records
 * }x Number of Groups
 *
 */

/*
 * .pdata FILE STRUCTURE
 *
 * *********Record***********************
 *
 * qint8              Record Type
 * qint8              Obtaining Type
 * QString            Record Name
 * QString            Description
 * QString            Name in source file
 * QString            Source File Name
 * QString            Source File Path
 * QString            Source File Type
 * QString            Computer Name create
 * QString            User Name create
 * QDate              Date create
 * QTime              Time create
 * QString            Computer Name modify
 * QString            User Name modify
 * QString            Date modify
 * QString            Time modify
 *
 **********Record2D***********************
 *
 * qint32             Length (number of points)
 * QString            x Units
 * QString            y Units
 *
 **********Record2DFun********************
 *
 * bool               Is fixed step
 * double             Step length
 * double             Maximum of function
 * double             Minimum of function
 *
 *****************************************
 */

 /*TODO:
  * LONGRUN
  * - import files DONE!
  * - plugins DONE!
  * - select graphs
  * - tracer
  * - graphs color template
  * - add, delete, copy, save records, record groups, files
  * - Fourier Transform
  * - analysis window band DONE!
  * - Digital Filters
  * - correct EXRescale DONE!
  * - make .probe file text
  * - reimplement rectodtreemodel (see PROBLEMS)
  * SHORTRUN
  * - make special layer for analyz window in QCustomPlot
  * - assign operator for RecordGroup DONE!
  * - reading pdata file should be implemented in virtual Record functions
  */

/*
 * PROBLEMS:
 * - bad RecordTreeModel class implementation. Course of RecordRootItem, which return
 * QModelIndex()

/*
 * BUGS:
 * - crash, when try to maximize window, with selected group
 * - when Zoom with drawn AnalysisWindow, artifact from zoom rect remains FIXED!
 * - write 0 (zero) when convert .csv in frist point in first graph/

/* NOTES:
/* note_1 (22.10.15)
 * While importing file it is sufficient just to reset Model
 * So plugin create probe file, then begin to reset model, then
 * call readprobefile function, which add items to Record Tree,
 * and then end reset model.
 * It is much harder to implement arbitrary adding, deleting, copying
 * records, groups and files because each operation should write data
 * into the file. Ideas:
 * -implement add/del/cut/copy children virtual functions for each RecordTreeItem subclass
 * -write to buffer in memory, than write to files
 * -make thread, which will write/read from files, create files etc
 */

