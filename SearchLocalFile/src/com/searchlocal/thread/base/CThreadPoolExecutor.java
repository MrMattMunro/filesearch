package com.searchlocal.thread.base;

import java.util.concurrent.BlockingQueue;
import java.util.concurrent.ThreadPoolExecutor;
import java.util.concurrent.TimeUnit;

import com.searchlocal.thread.ThreadManager;

public class CThreadPoolExecutor extends ThreadPoolExecutor {

	public CThreadPoolExecutor(int arg0, int arg1, long arg2, TimeUnit arg3,
			BlockingQueue<Runnable> arg4) {
		super(arg0, arg1, arg2, arg3, arg4);
		// TODO Auto-generated constructor stub
	}

	/**
	 * Method invoked upon completion of execution of the given Runnable. This
	 * method is invoked by the thread that executed the task. If non-null, the
	 * Throwable is the uncaught exception that caused execution to terminate
	 * abruptly. Note: To properly nest multiple overridings, subclasses should
	 * generally invoke <tt>super.afterExecute</tt> at the beginning of this
	 * method.
	 * 
	 * @param r
	 *            the runnable that has completed.
	 * @param t
	 *            the exception that caused termination, or null if execution
	 *            completed normally.
	 */
	protected void afterExecute(Runnable r, Throwable t) {
		ThreadManager manage = ThreadManager.getThreadManager();
		ThreadPoolExecutor pool = manage.getPool();
		BlockingQueue<Runnable> queue = pool.getQueue();
		if (queue.contains(r)) {
			queue.notifyAll();
		}
	}

	/**
	 * Method invoked prior to executing the given Runnable in the given thread.
	 * This method is invoked by thread <tt>t</tt> that will execute task
	 * <tt>r</tt>, and may be used to re-initialize ThreadLocals, or to
	 * perform logging. Note: To properly nest multiple overridings, subclasses
	 * should generally invoke <tt>super.beforeExecute</tt> at the end of this
	 * method.
	 * 
	 * @param t
	 *            the thread that will run task r.
	 * @param r
	 *            the task that will be executed.
	 */
	protected void beforeExecute(Thread t, Runnable r) {
		ThreadManager manage = ThreadManager.getThreadManager();
		ThreadPoolExecutor pool = manage.getPool();

		synchronized (this) {
			int poolsize = pool.getPoolSize();
			int maximumPoolSize = pool.getMaximumPoolSize();

			if (!(poolsize < maximumPoolSize)) {
				pool.setMaximumPoolSize(pool.getMaximumPoolSize() + 50);
			}
			// System.out.println(" Before Execute");
			// System.out.println("pool.getMaximumPoolSize() "+
			// pool.getMaximumPoolSize());
			// System.out.println("pool.getPoolSize(): " + pool.getPoolSize());
		}
	}
}
