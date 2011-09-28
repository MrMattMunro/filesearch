/**
 * $RCSfile: CheckSearcherTask.java
 * $Revision: 1.0
 * $Date: Jan 30, 2011
 *
 * Copyright (C) 2010 SlFile, Inc. All rights reserved.
 *
 * This software is the proprietary information of SlFile, Inc.
 * Use is subject to license terms.
 */
package com.web.searchlocal.flashpaper.thread;

import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.nio.ByteBuffer;
import java.nio.channels.Channels;
import java.nio.channels.ReadableByteChannel;
import java.util.ArrayList;
import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import com.web.searchlocal.thread.base.CRunnable;

/**
 * 监控搜索对象线程
 * 
 * <p>Title: 监控搜索对象线程</p>
 * <p>Description: </p>
 * <p>site: www.slfile.net</p>
 * @author changsong:qianjinfu@gmail.com
 * @version 1.0
 */
public class Covnert2SwfTask extends CRunnable {
	
	/**logger*/
	private Log logger = LogFactory.getLog(Covnert2SwfTask.class);

	/**inputFile*/
	private File inFile = null;

	/**outFilePath*/
	private File outFile = new File(System.getProperty("java.io.tmpdir"));

	/**default command*/
	private String defaultCommand = "FlashPrinter.exe";

	/**输出目录*/
	private File outFolder = null;

	public Covnert2SwfTask(File inFileObj, File outFilePath) {
		this.inFile = inFileObj;
		this.outFile = outFilePath == null ? outFolder : outFilePath;
	}

	/** 
	 * 执行
	 */
	public void excute() {
		String tmpOutFile = outFile.getPath().concat(File.separator).concat(
				inFile.getName().replaceAll("[.]{1}.*$", ".swf"));
		List<String> commandArray = new ArrayList<String>();
		commandArray.add(defaultCommand);
		commandArray.add(inFile.getPath());
		commandArray.add("-o");
		commandArray.add(tmpOutFile);
		ProcessBuilder pbObj = new ProcessBuilder();
		pbObj.command(commandArray);
		pbObj.directory(outFile);
		pbObj.redirectErrorStream(true);
		try {
			Process proObj = pbObj.start();
			final InputStream ins = proObj.getInputStream();
			final ByteBuffer byteBuffer = ByteBuffer.allocate(1024);
			Thread th = new Thread() {
				public void run() {
					ReadableByteChannel rbcObj = Channels.newChannel(ins);
					try {
						while (rbcObj.read(byteBuffer) != -1) {
							byteBuffer.flip();
							logger.info(java.nio.charset.Charset.defaultCharset()
									.decode(byteBuffer));
							byteBuffer.clear();
						}
					} catch (IOException e) {
						logger.error(e);
					}
				}
			};
			th.setDaemon(true);
			th.start();
			try {
				proObj.waitFor();
				logger.error("转换完成." + tmpOutFile);
			} catch (InterruptedException e) {
				logger.error(e);
			}
		} catch (IOException e) {
			logger.error(e);
		}
	}

	/** 
	 * 间隔执行
	 */
	public void run() {
		while (true) {
			synchronized (this) {
				excute();
			}
			try {
				System.out.println("执行周期开始");
				sleep(1 * 1000);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
	}
}
