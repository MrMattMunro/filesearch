package com.web.searchlocal.util;

import java.sql.Timestamp;
import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;

public class DateUtil {
	
	/**
	 *
	 * @return int
	 * @param sDate1 java.lang.String
	 * @param sDate2 java.lang.String
	 */
	public static int compareDate(String sDate1, String sDate2) {
		
		Date date1 = null;
		Date date2 = null;
		try {
			date1 = parse(sDate1);
			date2 = parse(sDate2);
		} catch (IllegalArgumentException e) {
			throw new IllegalArgumentException(e.getMessage());
		}
		
		long dif = 0;
		if (date2.after(date1))
			dif = (date2.getTime() - date1.getTime()) / 1000 / 60 / 60 / 24;
		else
			dif = (date1.getTime() - date2.getTime()) / 1000 / 60 / 60 / 24;
		
		return (int) dif;
	}
	
	private final static String[] dateFormats = { "yyyy-MM-dd", "yyyy-M-d", "yyyy-M-d", "yyyy-MM-dd", "yyyy-MM-dd HH:mm:ss" };
	

	public static String getDateTime(long time) {
		Date date = new Date(time);
		SimpleDateFormat df = new SimpleDateFormat(dateFormats[4]);
		String s = df.format(date);
		return s;
	}

	public static Date parse(String sDate) {
		Date date = null;
		boolean bParsed = false;
		String szErrorMsg = "";
		DateFormat dateFormat = null;
		dateFormat = DateFormat.getDateInstance();
		try {
			date = dateFormat.parse(sDate);
		} catch (ParseException e) {
			szErrorMsg = e.getMessage();
		}
		for (int i = 0; i < dateFormats.length; i++) {
			if (bParsed)
				break;
			dateFormat = new SimpleDateFormat(dateFormats[i]);
			try {
				date = dateFormat.parse(sDate);
				bParsed = true;
			} catch (ParseException e) {
				szErrorMsg += e.getMessage() + "\r\n";
			}
		}
		if (!bParsed) {
			throw new IllegalArgumentException(szErrorMsg + "\r\n"
					+ "Illegal Argument,can not parse input Date String");
		}
		
		return date;
	}
	
	public static String getNowDate() {
		SimpleDateFormat df = new SimpleDateFormat("yyyyMMdd");
		String s = df.format(new Date());
		return s;
	}
	
	public static String getNextDate() {
		Date date = new Date();
		Calendar cal = Calendar.getInstance();
		cal.setTime(date);
		cal.add(Calendar.MONTH, 3);
		date = cal.getTime();
		SimpleDateFormat df = new SimpleDateFormat("yyyyMMdd");
		String s = df.format(date);
		return s;
	}
	

	public static String getComputerCurrentDate() {
		Date date = new Date();
		SimpleDateFormat df = new SimpleDateFormat("yyyyMMdd");
		String s = df.format(date);
		return s;
	}
	

	public static String getCurrentDateTime() {
		SimpleDateFormat df = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
		String s = df.format(new Date());
		return s;
	}
	
	public static String getCurrentTime() {
		SimpleDateFormat df = new SimpleDateFormat("HH:mm:ss");
		return df.format(new Date());
	}
	
	public static String getCurrentDay() {
		String day;
		SimpleDateFormat df = new SimpleDateFormat("d");
		day = df.format(new Date());
		return day;
	}
	
	public static String getCurrentMonth() {
		String month;
		SimpleDateFormat df = new SimpleDateFormat("MM");
		month = df.format(new Date());
		return month;
	}

	public static String getCurrentYear() {
		SimpleDateFormat df = new SimpleDateFormat("yyyy");
		return df.format(new Date());
	}

	public static Long getLongDate(String strDate) {
		Date date = java.sql.Date.valueOf(strDate);
		Long lDate = new Long(date.getTime());
		return (lDate);
	}
	
	public static Long getLongDate(String strDate, int iType) {
		Long retDate = null;
		switch (iType) {
			case 0:
				retDate = getLongDate(strDate);
				break;
			case 1:
				retDate = new Long(java.sql.Timestamp.valueOf(strDate).getTime());
				break;
		}
		return retDate;
	}
	
	public static String getStrDate(java.lang.Long lDate, int iType) {
		Date date = new Date(lDate.longValue());
		SimpleDateFormat simpleDateFormat = null;
		switch (iType) {
			case 0:
				simpleDateFormat = new SimpleDateFormat("yyyy-MM-dd");
				break;
			case 1:
				simpleDateFormat = new SimpleDateFormat("yyyy-MM-dd HH");
				break;
			case 2:
				simpleDateFormat = new SimpleDateFormat("yyyy-MM-dd HH:mm");
				break;
			case 3:
				simpleDateFormat = new SimpleDateFormat("yyyyMMddHHmmss");
				break;
		}
		
		String strDate = simpleDateFormat.format(date);
		return (strDate);
	}

	public static String formatTimestamp(Timestamp timestamp, int iType) {
		String timeStr = "";
		if (timestamp != null) {
			timeStr = getStrDate(new Long(timestamp.getTime()), iType);
		}
		return timeStr;
	}
	
	public static String getDate(String aDate, int dif) {
		java.sql.Date date = null;
		try {
			date = java.sql.Date.valueOf(aDate);
		} catch (Exception e) {
			System.err.println("Application log:Catch Exception in getDate()");
			System.err.println("aDate:" + aDate);
			System.err.println(e.getMessage());
			e.printStackTrace();
			return null;
		}
		Calendar calendar = Calendar.getInstance();
		calendar.setTime(date);
		calendar.add(5, dif);
		SimpleDateFormat df = new SimpleDateFormat("yyyy-MM-dd");
		String s = df.format(calendar.getTime());
		return s;
	}
	
	public static String getDateAfterMonth(String aDate) {
		java.sql.Date date1 = null;
		try {
			date1 = java.sql.Date.valueOf(aDate);
		} catch (Exception e) {
			System.err.println("Application log:Catch Exception in getDateBeforeAMonth(String)");
			System.err.println("aDate:" + aDate);
			System.err.println(e.getMessage());
			e.printStackTrace();
			return null;
		}
		Calendar calendar = Calendar.getInstance();
		calendar.setTime(date1);
		calendar.add(2, 1);
		SimpleDateFormat df = new SimpleDateFormat("yyyy-MM-dd");
		String s = df.format(calendar.getTime());
		return s;
	} //eof getDateAfterMonth(aDate)
	

	public static String getDateAfterMonth(String aDate, int n) {
		
		Date date1 = null;
		try {
			date1 = parse(aDate);
		} catch (IllegalArgumentException e) {
			System.err.println("Application log:Catch Exception in getDateBeforeAMonth(String)");
			System.err.println("aDate:" + aDate);
			System.err.println(e.getMessage());
			e.printStackTrace();
			return null;
		}
		Calendar calendar = Calendar.getInstance();
		calendar.setTime(date1);
		calendar.add(2, 1);
		calendar.set(5, n);
		SimpleDateFormat df = new SimpleDateFormat("yyyy-MM-dd");
		String s = df.format(calendar.getTime());
		return s;
	}

	public static int getLastDate(String selectDate) {
		int dates = 0;
		Calendar calendar = Calendar.getInstance();
		
		try {
			calendar.setTime(parse(selectDate));
		} catch (Exception e) {
			throw new RuntimeException(e);
		}
		int year = calendar.get(1);
		switch (calendar.get(2) + 1) {
			default:
				break;
			
			case 1: // '\001'
				dates = 31;
				break;
			
			case 2: // '\002'
				if (year % 400 == 0 || year % 4 == 0 && year % 100 != 0)
					dates = 29;
				else
					dates = 28;
				break;
			
			case 3: // '\003'
				dates = 31;
				break;
			
			case 4: // '\004'
				dates = 30;
				break;
			
			case 5: // '\005'
				dates = 31;
				break;
			
			case 6: // '\006'
				dates = 30;
				break;
			
			case 7: // '\007'
				dates = 31;
				break;
			
			case 8: // '\b'
				dates = 31;
				break;
			
			case 9: // '\t'
				dates = 30;
				break;
			
			case 10: // '\n'
				dates = 31;
				break;
			
			case 11: // '\013'
				dates = 30;
				break;
			
			case 12: // '\f'
				dates = 31;
				break;
		}
		return dates;
	} 
	
	public static Timestamp toTimestamp(String dateString) {
		if ((dateString == null) || (dateString.trim().length() == 0)) {
			return null;
		}
		SimpleDateFormat format = new SimpleDateFormat("yyyy-MM-dd");
		try {
			Date date = format.parse(dateString.trim());
			return new Timestamp(date.getTime());
		} catch (ParseException e) {
		}
		return null;
	}
	
	public static void main(String[] args) {
	}
}