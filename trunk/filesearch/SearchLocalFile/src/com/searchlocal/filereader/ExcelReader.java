package com.searchlocal.filereader;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.Date;
import java.util.Iterator;
import java.util.List;

import org.apache.poi.hssf.usermodel.HSSFCell;
import org.apache.poi.hssf.usermodel.HSSFDateUtil;
import org.apache.poi.hssf.usermodel.HSSFRow;
import org.apache.poi.hssf.usermodel.HSSFSheet;
import org.apache.poi.hssf.usermodel.HSSFWorkbook;
import org.apache.poi.xssf.usermodel.XSSFCell;
import org.apache.poi.xssf.usermodel.XSSFRow;
import org.apache.poi.xssf.usermodel.XSSFSheet;
import org.apache.poi.xssf.usermodel.XSSFWorkbook;

import com.searchlocal.bean.ExcelFileBean;
import com.searchlocal.exception.LogicException;
import com.searchlocal.util.CLogger;
import com.searchlocal.util.StringUtils;

public class ExcelReader {

	private static CLogger logger = new CLogger(ExcelReader.class);

	public List getExcelFile(String filepath) throws LogicException {

		InputStream inputStream = null;
		try {
			inputStream = new FileInputStream(filepath);
			if (StringUtils.is2007Doc(filepath)) {
				XSSFWorkbook book = new XSSFWorkbook(inputStream);
				return getBeanList(book);
			} else {
				HSSFWorkbook book = new HSSFWorkbook(inputStream);
				return getBeanList(book);
			}
		} catch (FileNotFoundException e) {
			logger.error("LG_E001", filepath);
			throw new LogicException("LG_E001", e);
		} catch (IOException e) {
			logger.error("LG_E003", filepath);
			throw new LogicException("LG_E003", e);
		} finally {
			if (inputStream != null) {
				try {
					inputStream.close();
				} catch (IOException e) {
					e.printStackTrace();
				}
			}
		}
	}

	private static List getBeanList(HSSFWorkbook workbook) {
		HSSFSheet sheet;
		HSSFRow row;
		HSSFCell cell;
		String value;
		List<ExcelFileBean> beanList = new ArrayList<ExcelFileBean>();
		ExcelFileBean filebean;
		for (int i = 0; i < workbook.getNumberOfSheets(); i++) {
			sheet = workbook.getSheetAt(i);
			String sheetName = workbook.getSheetName(i);
			for (int j = 0; j <= sheet.getLastRowNum(); j++) {
				row = sheet.getRow(j);
				String rowvalue = "";
				if (row != null) {
					for (Iterator iter = row.cellIterator(); iter.hasNext();) {
						cell = (HSSFCell) iter.next();
						if (cell != null) {
							int cellType = cell.getCellType();
							value = getCellValue(cell, cellType);
							if (value != null && !"".equals(value)) {
								rowvalue = rowvalue + "," + value;
							}
						}
					}
					if (rowvalue != null && !"".equals(rowvalue)) {
						filebean = new ExcelFileBean();
						rowvalue = rowvalue.substring(1);
						filebean.setContent(rowvalue);
						filebean.setRownb(j + 1);
						filebean.setSheetname(sheetName);
						beanList.add(filebean);
					}
				}
			}
		}
		return beanList;
	}

	private static List getBeanList(XSSFWorkbook workbook) {
		XSSFSheet sheet;
		XSSFRow row;
		XSSFCell cell;
		String value;
		List<ExcelFileBean> beanList = new ArrayList<ExcelFileBean>();
		ExcelFileBean filebean;
		for (int i = 0; i < workbook.getNumberOfSheets(); i++) {
			workbook.getSheetAt(i);
			sheet = workbook.getSheetAt(i);
			String sheetName = workbook.getSheetName(i);
			for (int j = 0; j <= sheet.getLastRowNum(); j++) {
				row = sheet.getRow(j);
				String rowvalue = "";
				if (row != null) {
					for (Iterator iter = row.cellIterator(); iter.hasNext();) {
						cell = (XSSFCell) iter.next();
						if (cell != null) {
							int cellType = cell.getCellType();
							value = getCellValue(cell, cellType);
							if (value != null && !"".equals(value)) {
								rowvalue = rowvalue + "," + value;
							}
						}
					}
					if (rowvalue != null && !"".equals(rowvalue)) {
						filebean = new ExcelFileBean();
						rowvalue = rowvalue.substring(1);
						filebean.setContent(rowvalue);
						filebean.setRownb(j + 1);
						filebean.setSheetname(sheetName);
						beanList.add(filebean);
					}
				}
			}
		}
		return beanList;
	}

	private static String getCellValue(HSSFCell cell, int cellType) {
		String returnvalue = "";
		switch (cellType) {
		case HSSFCell.CELL_TYPE_NUMERIC:
			if (HSSFDateUtil.isCellDateFormatted(cell)) {
				Date date = cell.getDateCellValue();
				returnvalue = date.toString();
				break;
			}
			returnvalue = String.valueOf(cell.getNumericCellValue());
			break;
		case HSSFCell.CELL_TYPE_STRING:
			returnvalue = cell.toString();
			break;
		case HSSFCell.CELL_TYPE_BOOLEAN:
			returnvalue = cell.getBooleanCellValue() ? "true" : "false";
			break;
		default:
			returnvalue = cell.toString();
			break;
		}
		return returnvalue;
	}

	private static String getCellValue(XSSFCell cell, int cellType) {
		String returnvalue = "";
		switch (cellType) {
		case XSSFCell.CELL_TYPE_NUMERIC:
			if (HSSFDateUtil.isCellDateFormatted(cell)) {
				Date date = cell.getDateCellValue();
				returnvalue = date.toString();
				break;
			}
			returnvalue = String.valueOf(cell.getNumericCellValue());
			break;
		case XSSFCell.CELL_TYPE_STRING:
			returnvalue = cell.toString();
			break;
		case XSSFCell.CELL_TYPE_BOOLEAN:
			returnvalue = cell.getBooleanCellValue() ? "true" : "false";
			break;
		default:
			returnvalue = cell.toString();
			break;
		}
		return returnvalue;
	}

	public static void main(String[] args) {
		try {
			ExcelReader reader = new ExcelReader();
			String excelFile = "E:\\test2007doc\\tasklist.xlsx";
			List excelFilet2007 = reader.getExcelFile(excelFile);
			System.out.println("ExcelText2007=======" + excelFilet2007.size());
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
}
