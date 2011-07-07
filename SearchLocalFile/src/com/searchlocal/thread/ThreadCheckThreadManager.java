package com.searchlocal.thread;

import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.ThreadPoolExecutor;
import java.util.concurrent.TimeUnit;

import com.searchlocal.thread.base.CThreadPoolExecutor;

/**
 * 线程检查执行线程管理
 * 
 * <p>Title: </p>
 * <p>Description: </p>
 * <p>site: www.slfile.net</p>
 * @author changsong:qianjinfu@gmail.com
 * @version 1.0
 */
public class ThreadCheckThreadManager {

	/** 线程管理类 */
	public static ThreadCheckThreadManager manage = null;

	/** 线程池 */
	private static CThreadPoolExecutor pool;

	/** 
	 * 构造器
	 */
	public ThreadCheckThreadManager() {
		ArrayBlockingQueue<Runnable> abq = new ArrayBlockingQueue<Runnable>(1);
		pool = new CThreadPoolExecutor(2, 2, 120000, TimeUnit.SECONDS, abq);
	}

	/**
	 * 取得线程池
	 * 
	 * @return 线程池
	 */
	public ThreadPoolExecutor getPool() {
		return pool;
	}

	public void executeThread(Runnable task) {
		pool.execute(task);
	}

	/**
	 * 取得线程管理类
	 * 
	 * @return 线程管理类
	 */
	public static ThreadCheckThreadManager getThreadManager() {
		if (null == manage) {
			manage = new ThreadCheckThreadManager();
		}
		return manage;
	}
}
