/**
 * $RCSfile: CreateCustomDicTask.java
 * $Revision: 1.0
 * $Date: Jan 30, 2011
 *
 * Copyright (C) 2010 SlFile, Inc. All rights reserved.
 *
 * This software is the proprietary information of SlFile, Inc.
 * Use is subject to license terms.
 */
package com.searchlocal.thread.customdic;

import java.io.File;

import com.searchlocal.constants.Constant;
import com.searchlocal.filereader.ExcelToDicReader;
import com.searchlocal.menu.MessageFrame;
import com.searchlocal.menu.SearchlocalApp;
import com.searchlocal.thread.base.CRunnable;
import com.searchlocal.thread.createindex.ReCreateIndex;
import com.searchlocal.util.CustomDicUtil;
import com.searchlocal.util.FileUtil;
import com.searchlocal.util.MenuMessageUtil;
import com.searchlocal.util.StringUtils;

/**
 * 监控字典文件
 * 
 * <p>Title: 监控字典文件线程</p>
 * <p>Description: </p>
 * <p>site: www.slfile.net</p>
 * @author changsong:qianjinfu@gmail.com
 * @version 1.0
 */
public class CreateCustomDicTask extends CRunnable {

	/** 消息体 */
	private static MenuMessageUtil msg = new MenuMessageUtil();

	/** 
	 * 执行
	 */
	public void excute() {
		// 字典文件
		String dicFilePath = Constant.path + "com\\searchlocal\\properties\\customdic.properties";
		File dicFile = new File(dicFilePath);
		// 字典文件存在的时候,才进行读取词汇
		if (dicFile.exists()) {
			// 清空自定义字典
			CustomDicUtil.prop.clear();
			SearchlocalApp.startWork(Constant.ToolTipsClassify.TOOLTIPS_UPDATINGINDEX);
			String tempDic = CustomDicUtil.getMsgbyId(Constant.DICFILE);
			String isOverWriter = CustomDicUtil.getMsgbyId(Constant.ISOVERWRITER);
			// 删除自定义字典
			dicFile.delete();
			String suffixname = StringUtils.suffixName(tempDic);
			String dicfilepath = Constant.dicpath + "custom.dic";
			// 选择覆盖原有的自定义词典
			if ("true".equals(isOverWriter)) {
				createDic(suffixname, tempDic, dicfilepath);
			} else {
				// 不覆盖原有的词典
				appendDic(suffixname, tempDic, dicfilepath);
			}

			// 删除字典文件里空行
			FileUtil.deleteNullLine(dicfilepath);

			// 删除已经编译后的词典
			FileUtil.delFolder(Constant.diccompilepath, false);

			// 增加了词库需要所有都需要重新建索引
			if (ReCreateIndex.listen()) {
				SearchlocalApp.completeWork();
			}
			String completeemsg = msg.getMsgbyId(Constant.info_updatedindex);
			MessageFrame.showmessage(completeemsg);
		}
	}


	/** 
	 * 新建字典文件
	 * 
	 * @param suffixname 后缀名
	 * @param filepath 选择的文件路径
	 * @param dicfilepath 字典文件路径
	 */
	private void createDic(String suffixname, String filepath, String dicfilepath) {
		// 当是文本文件时
		if (suffixname.endsWith(Constant.FileClassify.TXT)) {
			File txtfile = new File(filepath);
			FileUtil.copyFile(txtfile, new File(dicfilepath));
		}
		// 当是xls文件时
		if (suffixname.endsWith(Constant.FileClassify.XLS)
				|| suffixname.endsWith(Constant.FileClassify.XLS2007)) {
			File excelfile = new File(filepath);
			ExcelToDicReader.getExcelFile(excelfile, new File(dicfilepath));
		}
	}


	/** 
	 * 字典文件存在,追加到字典文件
	 * 
	 * @param suffixname 后缀名
	 * @param filepath 选择的文件路径
	 * @param dicfilepath 字典文件路径
	 */
	private void appendDic(String suffixname, String filepath, String dicfilepath) {
		String temp = "";
		// 当是文本文件时
		if (suffixname.endsWith(Constant.FileClassify.TXT)) {
			temp = FileUtil.readText(filepath);
		}
		// 当是xls文件时
		if (suffixname.endsWith(Constant.FileClassify.XLS)
				|| suffixname.endsWith(Constant.FileClassify.XLS2007)) {
			temp = ExcelToDicReader.getExcelContent(new File(filepath));
		}
		FileUtil.appendText(dicfilepath, temp);
	}

	/** 
	 * 运行
	 */
	public void run() {
		while (true) {
			synchronized (this) {
				excute();
				System.out.println("监控字典文件检索结束");
			}
			try {
				System.out.println("监控字典文件检索开始");
				sleep(1 * 5000);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
	}
}
