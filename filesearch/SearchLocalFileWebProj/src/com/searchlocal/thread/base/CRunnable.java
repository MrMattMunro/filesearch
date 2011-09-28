package com.web.searchlocal.thread.base;

public abstract class CRunnable extends Thread implements Runnable, Cloneable {

	public void run() {
	}

	public CRunnable clone() {
		try {
			CRunnable cr = (CRunnable) super.clone();
			return cr;

		} catch (CloneNotSupportedException e) {
			e.printStackTrace();
			return null;
		}
	}
}
