#-*- coding: utf-8 -*-

import sys
import os
import win32com.client

if __name__ == "__main__":

    excel = win32com.client.DispatchEx("Excel.Application")
    excel.Visible = False
    book = excel.Workbooks.Open(os.path.join(os.path.dirname(sys.argv[0]), "test.xls"))
    sheet = book.Worksheets("sheet1")
    
    #乘法表
    for i in range(1, 10):
        for j in range(1, i + 1):
            sheet.Cells(i, j).Value = "%dx%d=%d" % (j, i, i * j)

    book.Close(SaveChanges=1)
    excel.Quit()
    
    

