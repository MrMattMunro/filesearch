package com.web.searchlocal.flashpaper;

import java.io.File;

/**
 * �ĵ�ת���ӿ�
 * @author 
 * @version 2009-12-3
 */
public interface FileConvert {
	
	/**
	 * ���ļ���ķ�ʽ������Ӧ��Ϣ
	 * @param response ��Ӧ��
	 * @return true/false
	 * @throws HDException �׳��쳣��Log
	 */
	//    boolean doResponseContent(HttpServletResponse response) throws HDException;
	/**
	 * ȡת������ļ�ʵ��
	 * @return fileInst/null �ļ�ʵ��/null
	 */
	//    File getFileInst();
	
	/**
	 * �ļ�ת��
	 * @param inputFileInst Դ�ļ�ʵ��
	 * @param outputFileInst ���Ŀ¼
	 * @return resultFileInst ת����ɺ���ļ�ʵ��
	 * @throws HDException �׳��쳣��Log
	 */
	File doConvertFile(File inputFileInst, File outputFileInst);

	/**
	 * �ļ�ת��
	 * @param inputFileInst Դ�ļ�ʵ��
	 * @return resultFileInst ת����ɺ���ļ�ʵ��
	 * @throws HDException �׳��쳣��Log
	 */
	File doConvertFile(File inputFileInst);

	/**
	 * �趨���Ŀ¼
	 * @param outFolder outFolder
	 * @throws HDException �׳��쳣��Log
	 */
	void setOutFolder(File outFolder);

	/**
	 * ��̬�趨�ⲿ����
	 * @param tmpCommand ���
	 */
	void setCommand(String tmpCommand);

	/**
	 * ȡ��ǰ���
	 * @return currCommand
	 */
	String getCommand();
}
