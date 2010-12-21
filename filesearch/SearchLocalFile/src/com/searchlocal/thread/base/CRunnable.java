package com.searchlocal.thread.base;

import com.searchlocal.param.CreateNewParam;
import com.searchlocal.thread.FileContainer;

public abstract class CRunnable extends Thread implements Runnable, Cloneable {

	public void init(CreateNewParam param, FileContainer filecon) {
	}
	
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
