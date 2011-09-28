package com.web.searchlocal.flashpaper.impl;

import java.io.File;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import com.web.searchlocal.flashpaper.FileConvert;
import com.web.searchlocal.flashpaper.thread.Covnert2SwfCore;

/**
 * �ļ�ת��swf��ʽ֧��
 * 
 * <p>Title: �ļ�ת��swf��ʽ֧��</p>
 * <p>Description: </p>
 * <p>site: www.slfile.net</p>
 * @author changsong:qianjinfu@gmail.com
 * @version 1.0
 */
public class FileConvert4SwfImpl implements FileConvert {

	/**logger*/
	private Log logger = LogFactory.getLog(FileConvert4SwfImpl.class);
	
	/**default command*/
	private String defaultCommand = "FlashPrinter.exe";
	
	/**ת����ɺ���ļ����*/
	private File fileInst = null;

	/**���Ŀ¼*/
	private File outFolder = null;

	/**
	 * {@inheritDoc}
	 * <strong>��Ҫ��֤fileInst�Ƿ�Ϊ��</strong>
	 */
	public File doConvertFile(File inputFileInst, File outFilePath) {
		Covnert2SwfCore.listen(inputFileInst, outFilePath);
		return null;
	}

	/**
	 * {@inheritDoc}
	 * <strong>��Ҫ��֤fileInst�Ƿ�Ϊ��</strong>
	 */
	public File doConvertFile(File inputFileInst) {
		return null;
	}

	/**
	 * setOutFolder
	 * @param setOutFolder setOutFolder
	 */
	public void setOutFolder(File setOutFolder) {
		this.outFolder = setOutFolder;
	}

	/**
	 * {@inheritDoc}
	 */
	public String getCommand() {
		return defaultCommand;
	}

	/**
	 * {@inheritDoc}
	 */
	public void setCommand(String tmpCommand) {
		this.defaultCommand = tmpCommand;
	}

	/**
	 * �������
	 * @param args �����б�
	 */
	public static void main(String[] args) {
		File inputFileInst = new File(
				"F:\\testdocfile\\Book1.xls"), outputFileInst = new File(
				"D:\\javahome\\Tomcat5.5\\webapps\\slfile");
		FileConvert fc = new FileConvert4SwfImpl();
		fc.doConvertFile(inputFileInst, outputFileInst);
	}

}
