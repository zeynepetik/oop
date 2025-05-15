#ifndef CELL_H
#define CELL_H

#include <string>
#include <memory>

namespace CellSpace {

class Cell {
public:
    virtual ~Cell() = default;
    virtual std::string getData() const = 0;
    virtual void setData(const std::string& data) = 0;
};

class ValueCell : public Cell {
public:
    //there is nothing to do in this class so abstract
    ~ValueCell() override = default;
};

class IntValueCell : public ValueCell {
private:
    int content;
public:
    IntValueCell(int val = 0);
    std::string getData() const override;
    void setData(const std::string& data) override;
};

class DoubleValueCell : public ValueCell {
private:
    double content;
public:
    DoubleValueCell(double val = 0.0);
    std::string getData() const override;
    void setData(const std::string& data);
};

class StringValueCell : public ValueCell {
private:
    std::string content;
public:
    StringValueCell(const std::string& val = "");
    std::string getData() const override;
    void setData(const std::string& data) override;
};

class FormulaCell : public Cell {
private:
    std::string content;
public:
    FormulaCell(const std::string& form = "");
    std::string getData() const override;
    void setData(const std::string& data) override;

};
}

#endif

