package com.searchlocal.thread.util;

import java.util.Date;

/**
 * 线程操作工具类
 * 
 * <p>Title: 同步文件任务</p>
 * <p>Description: </p>
 * <p>site: www.slfile.net</p>
 * @author changsong:qianjinfu@gmail.com
 * @version 1.0
 */
public class ThreadUtil {

	/**
	 * 线程等待
	 * 
	 */
	public static void wait(Object object) {
		try {
			object.wait();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	}

	/**
	 * 线程睡固定时间
	 * 
	 * @param millis 固定时间
	 */
	public static void sleep(long millis) {
		try {
			Thread.sleep(millis);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	}

	/**
	 * 判断是否到了中午
	 * 
	 * @return boolean 是否到了中午
	 */
	public static boolean isMidDay() {
		Date date = new Date();
		int hour = date.getHours();
		int minutes = date.getMinutes();
		return (hour == 12 && minutes < 10);
	}

	/**
	 * 判断是否过了正中午
	 * 
	 * @return boolean 是否过了正中午
	 */
	public static boolean isAferMidDay() {
		Date date = new Date();
		int hour = date.getHours();
		int minutes = date.getMinutes();
		return (hour == 12 && minutes > 30);
	}

}
