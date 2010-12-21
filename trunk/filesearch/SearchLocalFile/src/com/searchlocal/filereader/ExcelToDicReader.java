package com.searchlocal.filereader;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
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
import org.apache.poi.poifs.filesystem.POIFSFileSystem;
import org.apache.poi.xssf.usermodel.XSSFCell;
import org.apache.poi.xssf.usermodel.XSSFRow;
import org.apache.poi.xssf.usermodel.XSSFSheet;
import org.apache.poi.xssf.usermodel.XSSFWorkbook;

import com.searchlocal.constants.Constant;
import com.searchlocal.util.CLogger;
import com.searchlocal.util.StringUtils;

public class ExcelToDicReader {

	private static CLogger logger = new CLogger(ExcelReader.class);

	public static boolean getExcelFile(File excelfile, File dicFile) {

		InputStream inputStream = null;
		POIFSFileSystem fileSystem;
		HSSFWorkbook workbook = null;
		List wordList = null;
		try {
			inputStream = new FileInputStream(excelfile);
			String filepath = excelfile.getAbsolutePath();
			if (StringUtils.is2007Doc(filepath)) {
				XSSFWorkbook book = new XSSFWorkbook(inputStream);
				wordList = getWordList(book);
			} else {
				fileSystem = new POIFSFileSystem(inputStream);
				workbook = new HSSFWorkbook(fileSystem);
				wordList = getWordList(workbook);
			}
	
		} catch (FileNotFoundException e) {
			logger.error("LG_E001", excelfile.getAbsolutePath(), e);
		} catch (IOException e) {
			logger.error("LG_E003", excelfile.getAbsolutePath(), e);
		} finally {
			if (inputStream != null) {
				try {
					inputStream.close();
				} catch (IOException e) {
					e.printStackTrace();
				}
			}
		}

		copyFile(dicFile, wordList);
		return true;
	}
	
	public static List getWordList(HSSFWorkbook workbook) {
		HSSFSheet sheet;
		HSSFRow row;
		HSSFCell cell;
		String value;
		
		List<String> words = new ArrayList<String>();
		for (int i = 0; i < workbook.getNumberOfSheets(); i++) {
			sheet = workbook.getSheetAt(i);
			for (int j = 0; j <= sheet.getLastRowNum(); j++) {
				row = sheet.getRow(j);
				if (row != null) {
					for (Iterator iter = row.cellIterator(); iter.hasNext();) {
						cell = (HSSFCell) iter.next();
						if (cell != null) {
							int cellType = cell.getCellType();
							value = getCellValue(cell, cellType);
							if (value != null && !"".equals(value)) {
								words.add(value);
							}
						}
					}
				}
			}
		}
		return words;
	}
	
	public static List getWordList(XSSFWorkbook workbook) {
		XSSFSheet sheet;
		XSSFRow row;
		XSSFCell cell;
		String value;
		
		List<String> words = new ArrayList<String>();
		for (int i = 0; i < workbook.getNumberOfSheets(); i++) {
			sheet = workbook.getSheetAt(i);
			for (int j = 0; j <= sheet.getLastRowNum(); j++) {
				row = sheet.getRow(j);
				if (row != null) {
					for (Iterator iter = row.cellIterator(); iter.hasNext();) {
						cell = (XSSFCell) iter.next();
						if (cell != null) {
							int cellType = cell.getCellType();
							value = get2007CellValue(cell, cellType);
							if (value != null && !"".equals(value)) {
								words.add(value);
							}
						}
					}
				}
			}
		}
		return words;
	}
	
	public static String getExcelContent(File excelfile) {
		InputStream inputStream;
		POIFSFileSystem fileSystem;
		HSSFWorkbook workbook = null;
		try {
			inputStream = new FileInputStream(excelfile);
			fileSystem = new POIFSFileSystem(inputStream);
			workbook = new HSSFWorkbook(fileSystem);
		} catch (FileNotFoundException e) {
			logger.error("LG_E001", excelfile.getAbsolutePath(), e);
		} catch (IOException e) {
			logger.error("LG_E003", excelfile.getAbsolutePath(), e);
		}

		HSSFSheet sheet;
		HSSFRow row;
		HSSFCell cell;
		String value;
		
		StringBuffer bf = new StringBuffer();
		bf.append("\r\n");
		for (int i = 0; i < workbook.getNumberOfSheets(); i++) {
			sheet = workbook.getSheetAt(i);
			for (int j = 0; j <= sheet.getLastRowNum(); j++) {
				row = sheet.getRow(j);
				if (row != null) {
					for (Iterator iter = row.cellIterator(); iter.hasNext();) {
						cell = (HSSFCell) iter.next();
						if (cell != null) {
							int cellType = cell.getCellType();
							value = getCellValue(cell, cellType);
							if (value != null && !"".equals(value)) {
								 bf.append(value);
								 bf.append("\r\n"); 
							}
						}
					}
				}
			}
		}
		return bf.toString();
	}

	private static String get2007CellValue(XSSFCell cell, int cellType) {
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
		case HSSFCell.CELL_TYPE_BOOLEAN:
			returnvalue = cell.getBooleanCellValue() ? "true" : "false";
			break;
		default:
			returnvalue = cell.toString();
			break;
		}
		return returnvalue;
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
	
	private static void copyFile(File dicFile, List<String> values) {
		try{
			FileOutputStream fos = new FileOutputStream(dicFile);
			for (String b : values) {
				 fos.write(b.getBytes());
				 fos.write("\r\n".getBytes());
			}
			fos.close();
		}catch(Exception e){
			e.printStackTrace();
		}
	}
	
	public static void main(String[] args) {
		try {
			ExcelToDicReader reader = new ExcelToDicReader();
			String excelFile = "E:\\test2007doc\\tasklist.xlsx";
			String dicfilepath = Constant.dicpath + "custom.dic";
			boolean create = reader.getExcelFile(new File(excelFile), new File(dicfilepath));
			System.out.println("ExcelText2007=======" + create);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
}
