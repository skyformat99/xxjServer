/********************************************************************
    ����ʱ�䣺    2016/10/17  13:35:58 
    �ļ�����      MyGumbo.h
    ���ߣ�        лС��
    
    ���ܣ�        1.HTML��������
                2.
                
    ˵����        1. 
                2. 
*********************************************************************/
#include "src/gumbo.h"
#include <string.h>
#include <string>
#include <assert.h>

//tools ������
namespace CMyGumboTools {
// 	inline std::string handle_unknown_tag(GumboStringPiece *text)
// 	{
// 		std::string tagname = "";
// 		if (text->data == NULL) {
// 			return tagname;
// 		}
// 		// work with copy GumboStringPiece to prevent asserts 
// 		// if try to read same unknown tag name more than once
// 		GumboStringPiece gsp = *text;
// 		gumbo_tag_from_original_text(&gsp);
// 		tagname = std::string(gsp.data, gsp.length);
// 		return tagname;
// 
// 	}

	//��ȡ��ǩ����
	inline std::string get_tag_name(GumboNode *node)
	{
		if (!node)
			return "";

		std::string tagname;
		// work around lack of proper name for document node
		if (node->type == GUMBO_NODE_DOCUMENT) {
			tagname = "document";
		}
		else {
			tagname = gumbo_normalized_tagname(node->v.element.tag);
		}
		if (tagname.empty()) {
			tagname = "";
			GumboStringPiece *text = &node->v.element.original_tag;
			if (text)
			{
				if (text->data == NULL) {
					return tagname;
				}

				GumboStringPiece gsp = *text;
				gumbo_tag_from_original_text(&gsp);
				tagname = std::string(gsp.data, gsp.length);
			}
		}
		return tagname;
	}

	inline bool Equal(std::string key1, const std::string & key)
	{
		return (key1 == key);
	}
}
namespace CMyGumbo 
{
	//��ʼ��Htmlͷ
	inline GumboOutput * CreatGumbo(const std::string & html )
	{
		return gumbo_parse_with_options(&kGumboDefaultOptions, html.c_str(), html.length()+1);
	}

	//�ͷ�
	inline void Release(GumboOutput *& output)
	{
		if (output)
		{
			gumbo_destroy_output(&kGumboDefaultOptions, output);
			output = nullptr;
		}
	}

	//��ȡͷ�ڵ�
	inline GumboNode* GetHead(GumboNode* node) {
		GumboNode* head = NULL;
		if (node)
		{
			assert(node->type == GUMBO_NODE_ELEMENT);
			assert(node->v.element.children.length >= 2);

			const GumboVector* root_children = &node->v.element.children;

			for (int i = 0; i < root_children->length; ++i) {
				GumboNode* child = (GumboNode*)root_children->data[i];
				if (child->type == GUMBO_NODE_ELEMENT &&
					child->v.element.tag == GUMBO_TAG_HEAD) {
					head = child;
					break;
				}
			}
			assert(head != NULL);
		}

		return head;
	}

	//��ȡͷ�ڵ�
	inline GumboNode* GetBody(GumboNode* node) {
		GumboNode* body = NULL;
		if (node)
		{
			assert(node->type == GUMBO_NODE_ELEMENT);
			assert(node->v.element.children.length >= 2);

			const GumboVector* root_children = &node->v.element.children;

			for (int i = 0; i < root_children->length; ++i) {
				GumboNode* child = (GumboNode*)root_children->data[i];
				if (child->type == GUMBO_NODE_ELEMENT &&
					child->v.element.tag == GUMBO_TAG_BODY) {
					body = child;
					break;
				}
			}
			assert(body != NULL);
		}

		return body;
	}

	/*
		���ҽڵ�
		node:���ڵ�
		key:Ҫ���ҵĽڵ�����
		n:���ҵڼ����ڵ�
	*/
	inline GumboNode* Find(GumboNode* node, std::string key, int n=1)
	{
		GumboNode* element = nullptr;
		if (node)
		{
			GumboVector* head_children = &node->v.element.children;
			if (!head_children)
				return nullptr;

			int index = 0;
			for (int i = 0; i < head_children->length; ++i) {
				GumboNode* child = (GumboNode*)head_children->data[i];
				if (child && child->type == GUMBO_NODE_ELEMENT && CMyGumboTools::get_tag_name(child) == key)
				{
					index++;
					if (index >= n)//�ҵ���
					{
						element = child;
						break;
					}
				}
			}
		}

		return element;
	}

	inline GumboNode* Find(GumboNode* node, int n = 1)
	{
		GumboNode* element = nullptr;
		if (node)
		{
			GumboVector* head_children = &node->v.element.children;
			if (!head_children)
				return nullptr;

			int index = 0;
			for (int i = 0; i < head_children->length; ++i) {
				GumboNode* child = (GumboNode*)head_children->data[i];
				if (child)
				{
					index++;
					if (index >= n)//�ҵ���
					{
						element = child;
						break;
					}
				}
			}
		}

		return element;
	}

	//��ȡֵ
	inline std::string GetText(GumboNode* node)
	{
		GumboNode* title_text = node;
		if (!title_text)
			return "";

		assert(title_text->type == GUMBO_NODE_TEXT || title_text->type == GUMBO_NODE_WHITESPACE);
		if (title_text->type == GUMBO_NODE_TEXT || title_text->type == GUMBO_NODE_WHITESPACE)
		{
			return std::string(title_text->v.text.text);
		}
		else
		{
			return "";
		}
		
	}

	//��ȡInnerHTML
	inline std::string GetInnerHTML(GumboNode* node)
	{
		GumboNode* title_text = node;
		if (!title_text)
			return "";

		assert(title_text->type == GUMBO_NODE_TEXT || title_text->type == GUMBO_NODE_WHITESPACE);
		if (title_text->type == GUMBO_NODE_TEXT || title_text->type == GUMBO_NODE_WHITESPACE)
		{
			return std::string(title_text->v.text.original_text.data);
		}
		else
		{
			return "";
		}
	}

	//��ȡ����
	inline GumboAttribute* GetAttribute(GumboNode* node,const std::string & key)
	{
		if (node->type != GUMBO_NODE_ELEMENT) {
			return nullptr;
		}
		return gumbo_get_attribute(&node->v.element.attributes, key.c_str());
	}

	inline std::string GetText(GumboAttribute* node)
	{
		if (node)
		{
			return node->value;
		}

		return "";
	}

}