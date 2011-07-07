package com.searchlocal.util;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

import com.searchlocal.constants.Constant;

public class JpCodeUtil {

	/**
	 * @param args
	 */
	// TODO Auto-generated method stub
	// 正则表达式中对各字符集编码范围的总结
	// 这些字符集尤其是日文字符集的各种字、标点以及特殊符号的时候有所帮助。
	// UTF8
	// [\x01-\x7f]|[\xc0-\xdf][\x80-\xbf]|[\xe0-\xef][\x80-\xbf]{2}|[\xf0-\xff][\x80-\xbf]{3}
	// UTF16
	// [\x00-\xd7][\xe0-\xff]|[\xd8-\xdf][\x00-\xff]{2}
	// JIS
	// [\x20-\x7e]|[\x21-\x5f]|[\x21-\x7e]{2}
	// SJIS
	// [\x20-\x7e]|[\xa1-\xdf]|([\x81-\x9f]|[\xe0-\xef])([\x40-\x7e]|[\x80-\xfc])
	// EUC_JP
	// [\x20-\x7e]|\x81[\xa1-\xdf]|[\xa1-\xfe][\xa1-\xfe]|\x8f[\xa1-\xfe]{2}
	// EUC_JP标点符号及特殊字符
	// [\xa1-\xa2][\xa0-\xfe]
	// EUC_JP全角数字
	// \xa3[\xb0-\xb9]
	// EUC_JP全角大写英文
	// \xa3[\xc1-\xda]
	// EUC_JP全角小写英文
	// \xa3[\xe1-\xfa]
	// EUC_JP全角平假名
	// \xa4[\xa1-\xf3]
	// EUC_JP全角片假名 [color=Red]2007-03-12 15:00更新[/color]
	// \xa3[\xb0-\xb9]|\xa3[\xc1-\xda]|\xa5[\xa1-\xf6][\xa3][\xb0-\xfa]|[\xa1][\xbc-\xbe]|[\xa1][\xdd]
	// EUC_JP全角汉字 [color=Red]2007-03-12 15:06更新[/color]
	// [\xb0-\xcf][\xa0-\xd3]|[\xd0-\xf4][\xa0-\xfe]|[\xB0-\xF3][\xA1-\xFE]|[\xF4][\xA1-\xA6]|[\xA4][\xA1-\xF3]|[\xA5][\xA1-\xF6]|[\xA1][\xBC-\xBE]
	// Big5
	// [\x01-\x7f]|[\x81-\xfe]([\x40-\x7e]|[\xa1-\xfe])
	// GBK
	// [\x01-\x7f]|[\x81-\xfe][\x40-\xfe]
	// GB2312汉字
	// [\xb0-\xf7][\xa0-\xfe]
	// GB2312半角标点符号及特殊符号
	// \xa1[\xa2-\xfe]
	// GB2312罗马数组及项目序号
	// \xa2([\xa1-\xaa]|[\xb1-\xbf]|[\xc0-\xdf]|[\xe0-\xe2]|[\xe5-\xee]|[\xf1-\xfc])
	// GB2312全角标点及全角字母
	// \xa3[\xa1-\xfe]
	// GB2312日文平假名
	// \xa4[\xa1-\xf3]
	// GB2312日文片假名
	// \xa5[\xa1-\xf6]
	// 補充:
	// GB18030
	// [\x00-\x7f]|[\x81-\xfe][\x40-\xfe]|[\x81-\xfe][\x30-\x39][\x81-\xfe][\x30-\x39]
	// [color=Red]2007-03-12 21:35 补充[/color]
	// 日文半角空格
	// \x20
	// SJIS全角空格
	// (?:\x81\x81)
	// SJIS全角数字
	// (?:\x82[\x4f-\x58])
	// SJIS全角大写英文
	// (?:\x82[\x60-\x79])
	// SJIS全角小写英文
	// (?:\x82[\x81-\x9a])
	// SJIS全角平假名
	// (?:\x82[\x9f-\xf1])
	// SJIS全角平假名扩展
	// (?:\x82[\x9f-\xf1]|\x81[\x4a\x4b\x54\x55])
	// SJIS全角片假名
	// (?:\x83[\x40-\x96])
	// SJIS全角片假名扩展
	// (?:\x83[\x40-\x96]|\x81[\x45\x5b\x52\x53])
	// EUC_JP全角空格
	// (?:\xa1\xa1)
	// EUC半角片假名
	// (?:\x8e[\xa6-\xdf])
	// 1. GBK (GB2312/GB18030)
	// \x00-\xff GBK双字节编码范围
	// \x20-\x7f ASCII
	// \xa1-\xff 中文
	// \x80-\xff 中文
	//
	// 2. UTF-8 (Unicode)
	// \u4e00-\u9fa5 (中文)
	// \u0800-\u4e00 (日文)
	public static String checkJPCharacters(String str) {
		// 1. GBK (GB2312/GB18030)
		// \x00-\xff GBK双字节编码范围
		// \x20-\x7f ASCII
		// \xa1-\xff 中文
		// \x80-\xff 中文
		//
		// 2. UTF-8 (Unicode)
		// \u4e00-\u9fa5 (中文)
		// \u0800-\u4e00 (日文)
		String[] regExs = new String[] { "[\u0800-\u4e00]", "[\u4e00-\u9fa5]" };
		String laguage = "";
		for (int i = 0; i < regExs.length; i++) {
			String regEx = regExs[i];
			Pattern p = Pattern.compile(regEx);
			Matcher m = p.matcher(str);
			while (m.find()) {
				switch (i) {
				case 0:
					laguage = Constant.LanguageClassify.JAPANESE;
					break;
				case 1:
					laguage = Constant.LanguageClassify.CHINESE;
					break;
				default:
					laguage = Constant.LanguageClassify.CHINESE;
					break;
				}
			}
		}
		return laguage;
	}
}
