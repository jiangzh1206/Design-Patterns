#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <memory>
using namespace std;

struct HtmlBuilder;

struct HtmlElement
{
    string name;
    string text;
    vector<HtmlElement> elements;
    const size_t indent_size = 2;

    static unique_ptr<HtmlBuilder> build(const string& root_name)
    {
        return make_unique<HtmlBuilder>(root_name);
    }

    HtmlElement() {}
    HtmlElement(const string& name, const string& text)
        : name(name), text(text)
    {
        ;
    }

    string str(int indent = 0) const
    {
        // pretty print
        ostringstream oss;
        string i(indent_size * indent, ' ');
        oss << i << "<" << name << ">" << endl;
        if (text.size() > 0)
            oss << string(indent_size * (indent + 1), ' ') << text << endl;

        for (const auto& e : elements)
            oss << e.str(indent + 1);

        oss << i << "</" << name << ">" << endl;
        return oss.str();
    }
};

struct HtmlBuilder
{
    HtmlElement root;
    HtmlBuilder(string root_name) { root.name = root_name; }

    operator HtmlElement() const { return root; }

    HtmlBuilder& add_child(string child_name, string child_next)
    {
        HtmlElement e{child_name, child_next};
        root.elements.emplace_back(e);
        return *this;
    }
    HtmlBuilder* add_child_2(string child_name, string child_text)
    {
        HtmlElement e{child_name, child_text};
        root.elements.emplace_back(e);
        return this;
    }
    string str() const
    {
        return root.str();
    }
};

namespace html
{
    struct Tag
    {
        std::string name;
        std::string text;
        std::vector<Tag> children;
        std::vector<std::pair<std::string, std::string>> attributes;

        friend std::ostream& operator<<(std::ostream& os, const Tag& tag)
        {
            os << "<" << tag.name;

            for (const auto& att : tag.attributes)
                os << " " << att.first << "=\"" << att.second << "\"";

            if (tag.children.size() == 0 && tag.text.length() == 0) {
                os << "/>" << std::endl;
            } else {
                os << ">" << std::endl;

                if (tag.text.length())
                    os << tag.text << std::endl;

                for (const auto& child : tag.children)
                    os << child;

                os << "</" << tag.name << ">" << std::endl;
            }

            return os;
        }

    protected:

        Tag(const std::string& name, const std::string& text)
            : name{name},
              text{text}
        {
        }


        Tag(const std::string& name, const std::vector<Tag>& children)
            : name{name},
              children{children}
        {
        }
    };

    struct P : Tag
    {
        explicit P(const std::string& text)
            : Tag{"p", text}
        {
        }

        P(std::initializer_list<Tag> children)
            : Tag("p", children)
        {
        }
    };

    struct IMG : Tag
    {
        explicit IMG(const std::string& url)
            : Tag{"img", ""}
        {
            attributes.emplace_back(make_pair("src", url));
        }
    };
}

inline int simple_test()
{

    using namespace html;

    std::cout <<
        P{
          IMG {"http://pokemon.com/pikachu.png"}
        }
    << std::endl;


    // <p>hello</p>
    auto text = "hello";
    string output;
    output += "<p>";
    output += text;
    output += "</p>";
    printf("<p>%s</p>", text);

    // <ul><li>hello</li><li>world</li></ul>
    string words[] = {"hello", "world"};
    ostringstream oss;
    oss << "<ul>";
    for (auto w : words)
        oss << "  <li>" << w << "</li>";
    oss << "</ul>";
    printf(oss.str().c_str());

    // easier
    HtmlBuilder builder{"ul"};
    builder.add_child("li", "hello").add_child("li", "world");
    cout << builder.str() << endl;


    auto builder2 = HtmlElement::build("ul")
        ->add_child_2("li", "hello")->add_child_2("li", "world");
    cout << builder2 << endl;


    return 0;
}

