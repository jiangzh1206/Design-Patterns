#include <iostream>
#include <string>
#include <sstream>
#include <memory>
#include <vector>
using namespace std;


enum class OutputFormat
{
    Markdown,
    Html,
};

struct ListStrategy
{
    virtual ~ListStrategy() = default;
    virtual void start(ostringstream& oss) = 0;
    virtual void end(ostringstream& oss) = 0;
    virtual void add_list_item(ostringstream& oss, const std::string& item) = 0;
};

struct MarkdownStrategy : ListStrategy
{
    void start(ostringstream& oss) override
    {
		;
    }

    void end(ostringstream& oss) override
    {
		;
    }

    void add_list_item(ostringstream& oss, const std::string& item) override
    {
		oss << " * " << item << endl;
    }
};
  
struct HtmlStrategy : ListStrategy
{
    void start(ostringstream& oss) override
    {
		oss << "<ul>" << endl;
    }

    void end(ostringstream& oss) override
    {
		oss << "</ul>" << endl;
    }

    void add_list_item(ostringstream& oss, const std::string& item) override
    {
		oss << "<li>" << item << "</li>" << endl;
    }
};

// dynamic strategy
struct TextProcessorD
{
	void clear() {oss_.str(""); oss_.clear();}
	void append_list(const vector<string>& item) 
	{
		list_strategy_->start(oss_);
		for (auto& item : items) {
			list_strategy_->add_list_item(item);
		}
		list_strategy_->end(oss_);
	}
	void set_output_format(const OutputFormat format)
	{
		switch(format) 
		{
		case: OutputFormat::Markdown:
			list_strategy_ = make_unique<MarkdownStrategy>();
			break;
		case: OutputFormat::Html:
			list_strategy_ = make_unique<HtmlStrategy>();
			break;
		default:
			throw runtime_error("Unsupported strategy.");
		}
	}
	string str()const { return oss.str();}
private:
	ostringstream oss_;
	unique_ptr<ListStrategy> list_strategy_;
};

// static strategy
template <typename LS>
struct TextProcessorS
{
	void clear() {oss_.str(""); oss_.clear();}
		void append_list(const vector<string>& item) 
	{
		list_strategy_->start(oss_);
		for (auto& item : items) {
			list_strategy_->add_list_item(item);
		}
		list_strategy_->end(oss_);
	}
	string str()const { return oss.str();}
private:
	ostringstream oss_;
	LS list_strategy_;
}

int main_()
{
	// danymic
	TextProcessorD tp;
	tp.set_output_format(OutputFormat::Html);
	tp.append_list({"aaa", "bbb", "ccc"});
	cout << tp.str() << endl;
	
	// static strategy
	TextProcessorS<MarkdownListStrategy> tpm;
	tpm.append_list({"aaa", "bbb", "ccc"});
	cout << tpm.str() << endl;
}