Set objShell = CreateObject("Wscript.Shell")

strPath = Wscript.ScriptFullName
strPath = LEFT(strPath, (LEN(strPath)-16))
strPath = strPath + "Excel_Refreshed.xlsm"


Dim xlApp, xlBook, xlSheet


set xlApp = CreateObject("Excel.Application")

Set xlBook = xlApp.Workbooks.Open(strPath)

Set xlSheet = xlBook.worksheets.item(1)



xlBook.Application.Run "Excel_Refreshed.xlsm!Update_txtdata_location" 
xlbook.Save

xlbook.Close

xlApp.Quit



Set xlSheet = Nothing

Set xlApp = Nothing 

Set xlBook = Nothing 