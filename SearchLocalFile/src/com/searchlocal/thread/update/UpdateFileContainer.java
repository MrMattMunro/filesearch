/**
 * $RCSfile: UpdateFileContainer.java
 * $Revision: 1.0
 * $Date: Jan 30, 2011
 *
 * Copyright (C) 2010 SlFile, Inc. All rights reserved.
 *
 * This software is the proprietary information of SlFile, Inc.
 * Use is subject to license terms.
 */
package com.searchlocal.thread.update;

import java.util.concurrent.ConcurrentHashMap;

/**
 * 更新文件容器
 * 
 * <p>Title: 更新文件容器</p>
 * <p>Description: </p>
 * <p>site: www.slfile.net</p>
 * @author changsong:qianjinfu@gmail.com
 * @version 1.0
 */
public class UpdateFileContainer {

	/** 需插入文件 */
	private static ConcurrentHashMap<String, Long> addfile = new ConcurrentHashMap<String, Long>();;
	
	/** 需删除文件 */
	private static ConcurrentHashMap<String, Long> delfile = new ConcurrentHashMap<String, Long>();;

	/** 是否完成标志位 */
	private static boolean isdone = false;

	/**
	 * 取得是否完成标志位
	 */
	public boolean isIsdone() {
		return isdone;
	}

	/**
	 * 设置是否完成标志位
	 */
	public void setIsdone(boolean isdone) {
		UpdateFileContainer.isdone = isdone;
	}

	/**
	 * 放入需插入文件
	 * 
	 * @param path 文件路径
	 * @param modify 最后修改时间
	 */
	public synchronized void putAddfile(String path, Long modify) {
		addfile.put(path, modify);
		notifyAll();
	}
	
	/**
	 * 放入需删除文件
	 * 
	 * @param path 文件路径
	 * @param modify 最后修改时间
	 */
	public synchronized void putDelfile(String path, Long modify) {
		delfile.put(path, modify);
		notifyAll();
	}
	
	/**
	 * 删除需插入文件
	 * 
	 * @param path 文件路径
	 * @param modify 最后修改时间
	 */
	public synchronized void removeAddfile(String path) {
		addfile.remove(path);
		notifyAll();
	}
	
	/**
	 * 删除需删除文件
	 * 
	 * @param path 文件路径
	 * @param modify 最后修改时间
	 */
	public synchronized void removeDelfile(String path) {
		delfile.remove(path);
		notifyAll();
	}

	/**
	 * 取得插入文件的个数
	 */
	public synchronized int getAddfileNum() {
		return addfile.size();
	}
	
	/**
	 * 取得删除文件的个数
	 */
	public synchronized int getDelfileNum() {
		return delfile.size();
	}
	
	/**
	 * 取得需要删除的文件
	 */
	public synchronized ConcurrentHashMap<String, Long> getDelfile() {
		return delfile;
	}

	/**
	 * 取得需要添加的文件
	 */
	public synchronized ConcurrentHashMap<String, Long> getAndfile() {
		return addfile;
	}

	/**
	 * 清楚容器里的文件
	 */
	public synchronized void clearAll() {
		addfile.clear();
		delfile.clear();
	}
}
