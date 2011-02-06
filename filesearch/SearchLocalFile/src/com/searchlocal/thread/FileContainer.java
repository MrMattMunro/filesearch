package com.searchlocal.thread;

import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.ConcurrentLinkedQueue;

import com.searchlocal.constants.Constant;
import com.searchlocal.param.FileParam;

public class FileContainer {

	private static ConcurrentHashMap<String, Long> insertedfile = new ConcurrentHashMap<String, Long>();;

	private static ConcurrentHashMap<String, Long> haserrorfile = new ConcurrentHashMap<String, Long>();

	private static ConcurrentLinkedQueue<FileParam> allfile = new ConcurrentLinkedQueue<FileParam>();

	private static boolean isdone = false;

	/**
	 * @return the isdone
	 */
	public static boolean isIsdone() {
		return isdone;
	}

	/**
	 * @param isdone the isdone to set
	 */
	public static void setIsdone(boolean isdone) {
		FileContainer.isdone = isdone;
	}

	/**
	 * @return Returns the haserrorfile.
	 */
	public synchronized void putfile(String path, Long modify) {
		FileParam fileParam = new FileParam();
		fileParam.setError(Constant.NO_ERROR);
		fileParam.setPath(path);
		fileParam.setLastModify(modify);
		allfile.add(fileParam);
		notifyAll();
	}

	/**
	 * @return Returns the haserrorfile.
	 */
	public synchronized FileParam getfile() {
		FileParam param = null;
		if (!allfile.isEmpty()) {
			param = allfile.poll();
		}
		notifyAll();
		return param;
	}

	/**
	 * @return Returns the haserrorfile.
	 */
	public synchronized void putinsertedfile(String path, Long modify) {
		insertedfile.put(path, modify);
		notifyAll();
	}

	/**
	 * @return Returns the haserrorfile.
	 */
	public synchronized FileParam getinsertedfile(String key) {
		FileParam param = new FileParam();
		while (insertedfile.size() == 0) {
			try {
				wait();
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}

		if (insertedfile.size() != 0) {
			Long lastmodify = (Long) insertedfile.get(key);
			param.setPath(key);
			param.setLastModify(lastmodify);
			notifyAll();
		}
		return param;
	}

	/**
	 * @return Returns the haserrorfile.
	 */
	public synchronized int getInsertedfileNum() {
		return insertedfile.size();
	}

	/**
	 * @return Returns the haserrorfile.
	 */
	public synchronized int getHaserrorfileNum() {
		return haserrorfile.size();
	}

	/**
	 * @return Returns the haserrorfile.
	 */
	public synchronized void puthaserrorfile(String path, Long modify) {
		haserrorfile.put(path, modify);
		notifyAll();
	}

	/**
	 * @return Returns the haserrorfile.
	 */
	public synchronized FileParam gethaserrorfile(String key) {
		FileParam param = new FileParam();
		while (haserrorfile.size() == 0) {
			try {
				wait();
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}

		if (haserrorfile.size() != 0) {
			Long lastmodify = (Long) haserrorfile.get(key);
			param.setPath(key);
			param.setLastModify(lastmodify);
			notifyAll();
		}
		return param;
	}

	/**
	 * @return Returns the allfile.
	 */
	public synchronized ConcurrentLinkedQueue<FileParam> getAllfile() {
		return allfile;
	}

	/**
	 * @return Returns the haserrorfile.
	 */
	public synchronized ConcurrentHashMap<String, Long> getHaserrorfile() {
		return haserrorfile;
	}

	/**
	 * @return Returns the insertedfile.
	 */
	public synchronized ConcurrentHashMap<String, Long> getInsertedfile() {
		return insertedfile;
	}

	/**
	 * @return Returns the insertedfile.
	 */
	public synchronized void clearAll() {
		haserrorfile.clear();
		allfile.clear();
	}

}
