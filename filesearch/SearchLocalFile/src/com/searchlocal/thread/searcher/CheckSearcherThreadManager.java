/**
 * $RCSfile: CheckSearcherThreadManager.java
 * $Revision: 1.0
 * $Date: Jan 30, 2011
 *
 * Copyright (C) 2010 SlFile, Inc. All rights reserved.
 *
 * This software is the proprietary information of SlFile, Inc.
 * Use is subject to license terms.
 */
package com.searchlocal.thread.searcher;

import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.ThreadPoolExecutor;
import java.util.concurrent.TimeUnit;

import com.searchlocal.thread.base.CThreadPoolExecutor;

/**
 *  监控搜索对象的线程管理类
 * 
 * <p>Title: 监控搜索对象的线程管理类</p>
 * <p>Description: </p>
 * <p>site: www.slfile.net</p>
 * @author changsong:qianjinfu@gmail.com
 * @version 1.0
 */
public class CheckSearcherThreadManager {

	/** 线程管理类 */
	public static CheckSearcherThreadManager manage = null;

	/** 线程池 */
	private static CThreadPoolExecutor pool;

	/** 
	 * 构造器
	 */
	public CheckSearcherThreadManager() {

		ArrayBlockingQueue<Runnable> abq = new ArrayBlockingQueue<Runnable>(1);
		pool = new CThreadPoolExecutor(2, 2, 1200, TimeUnit.SECONDS, abq);
	}

	/**
	 * 取得线程池
	 * 
	 * @return Returns the pool.
	 */
	public ThreadPoolExecutor getPool() {
		return pool;
	}

	/**
	 * 执行线程
	 * 
	 * @param task 线程
	 */
	public void executeThread(Runnable task) {
		pool.execute(task);
	}

	/**
	 * 取得线程管理类
	 * 
	 * @return 线程管理类
	 */
	public static CheckSearcherThreadManager getThreadManager() {
		if (null == manage) {
			manage = new CheckSearcherThreadManager();
		}
		return manage;
	}
}
