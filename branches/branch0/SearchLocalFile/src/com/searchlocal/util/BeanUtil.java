/**
 * $RCSfile: BeanUtil.java
 * $Revision: 1.0
 * $Date: Jan 30, 2011
 *
 * Copyright (C) 2010 SlFile, Inc. All rights reserved.
 *
 * This software is the proprietary information of SlFile, Inc.
 * Use is subject to license terms.
 */
package com.searchlocal.util;

import org.apache.lucene.document.Document;

import com.searchlocal.bean.ResultBean;
import com.searchlocal.constants.Constant;

/**
 * 生成检索对象
 * 
 * <p>Title: 创建搜索对象时,数据存储对象</p>
 * <p>Description: </p>
 * <p>site: www.slfile.net</p>
 * @author changsong:qianjinfu@gmail.com
 * @version 1.0
 */
public class BeanUtil {

	/**消息体 */
	private static MenuMessageUtil msg = new MenuMessageUtil();

	/**
	 * 创建搜索对象时,数据存储对象
	 * 
	 * @param element 检索的内容
	 * @param content 内容
	 */
	public static ResultBean getBean(Document element, String content) {
		// 文件名
		String filename = element.get("filename");
		// 文件路径
		String absolutepath = element.get("path");
		// 最新更新时间
		String lastmodify = element.get("lastmodify");
		StringBuffer buf = new StringBuffer();

		buf.append(lastmodify.substring(0, 4));
		buf.append("-");
		buf.append(lastmodify.substring(4, 6));
		buf.append("-");
		buf.append(lastmodify.substring(6, 8));
		buf.append("/");
		buf.append(lastmodify.substring(8, 10));
		buf.append(":");
		buf.append(lastmodify.substring(10, lastmodify.length()));
		lastmodify = buf.toString();

		ResultBean filebean = new ResultBean();
		filebean.setFileName(filename);
		filebean.setFilePath(absolutepath);
		filebean.setContent(content);
		filebean.setLastmodify(lastmodify);

		// 描述
		String the = (String) msg.getMsgbyId(Constant.web_the);
		String row = (String) msg.getMsgbyId(Constant.web_row);
		String webpage = (String) msg.getMsgbyId(Constant.web_page);

		// 取得后缀名
		String attachstring = "";
		String suffixname = StringUtils.suffixName(filename);
		if (suffixname.equals(Constant.FileClassify.DOC)
				|| suffixname.equals(Constant.FileClassify.DOC2007)) {
			String paragraphNo = element.get("paragraphNo");
			String web_paragraphNo = (String) msg.getMsgbyId(Constant.web_photogragh);
			attachstring = filename + the + paragraphNo + web_paragraphNo;
			filebean.setDesp(attachstring);
			filebean.setFileType(Constant.FileNameClassify.WORD);
			return filebean;
		}
		if (suffixname.equals(Constant.FileClassify.XLS)
				|| suffixname.equals(Constant.FileClassify.XLS2007)) {
			String sheetname = element.get("sheetname");
			String excelthe = (String) msg.getMsgbyId(Constant.web_excel_the);
			String excelpage = (String) msg.getMsgbyId(Constant.web_excel_page);
			String rownb = element.get("rownb");
			attachstring = filename + excelthe + sheetname + excelpage + rownb + row;
			filebean.setDesp(attachstring);
			filebean.setFileType(Constant.FileNameClassify.EXCEL);
			return filebean;
		}
		if (suffixname.equals(Constant.FileClassify.PDF)) {
			String page = element.get("page");
			attachstring = filename + the + page + webpage;
			filebean.setDesp(attachstring);
			filebean.setFileType(Constant.FileNameClassify.PDF);
			return filebean;
		}
		if (suffixname.equals(Constant.FileClassify.PPT)
				|| suffixname.equals(Constant.FileClassify.PPT2007)) {
			String page = element.get("page");
			attachstring = filename + the + page + webpage;
			filebean.setDesp(attachstring);
			filebean.setFileType(Constant.FileNameClassify.PPT);
			return filebean;
		}
		if (suffixname.equals(Constant.FileClassify.CHM)) {
			attachstring = filename + the + element.get("catalogname")
					+ (String) msg.getMsgbyId(Constant.web_chapter);
			filebean.setDesp(attachstring);
			filebean.setFileType(Constant.FileNameClassify.CHM);
			return filebean;
		}
		if ((Constant.FileClassify.isHtmlcontain(suffixname))) {
			filebean.setDesp(filename);
			filebean.setFileType(Constant.FileNameClassify.HTML);
			return filebean;
		}
		if (Constant.SrcClassify.iscontain(suffixname)) {
			attachstring = filename + the + element.get("rownb") + row;
			filebean.setDesp(attachstring);
			filebean.setFileType(Constant.FileNameClassify.TXT);
			return filebean;
		}
		return null;
	}
}
