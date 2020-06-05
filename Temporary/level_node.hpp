#pragma once
#include <vector>
#include <unordered_map>
#include <istream>

class Level;
class LevelWorld;
class LevelScene;
class LevelSpace;
class Component;

class LevelNode
{
public :
    enum class NodeType
    {
        kScene,
        kSpace,
        kEntity
    };

    virtual ~LevelNode() = default;

    virtual bool initialize( std::istream& ) = 0;
    virtual void finalize() = 0;
    virtual NodeType getNodeType() const noexcept = 0;

    void setLevel( Level* Level ) noexcept { level_ = Level; }
    void setParent( LevelNode* Parent ) noexcept { parent_ = Parent; }
    void addChild( LevelNode* Child ) { childs_.push_back(Child); Child->setParent(this); }
    Level* getLevel() noexcept { return level_; }
    LevelNode* getChild( size_t Index=0 ) const noexcept { return Index<childs_.size() ? childs_[Index] : nullptr; }
    template <class NodeType_>
    NodeType_* getChild( size_t Index=0 ) const noexcept
    { 
        size_t count = 0;
        for( auto& child : childs_ )
        {
            if( child->getNodeType() == NodeType_::kNodeType &&
                count++ == Index )
            {
                return static_cast<NodeType_*>(child);
            }
        }
        return nullptr;
    }
    bool initializeEntry( std::istream& );
    void finalizeEntry();

private :
    Level* level_ = nullptr;
    LevelNode* parent_ = nullptr;
    std::vector<LevelNode*> childs_;
    std::unordered_map<uint32_t, Component*> components_;
};

 // 初期化の再帰的呼び出し
 // より親の処理が先に呼び出される
bool LevelNode::initializeEntry( std::istream& DataStream )
{
    if( !initialize(DataStream) ) return false;

    const size_t kChildsNum = childs_.size();
    for( size_t i=0; i<kChildsNum; ++i )
    {
        if( !childs_.at(i)->initializeEntry(DataStream) )
        { // この初期化に失敗
            // すでに初期化済みのノードを開放する
            for( int j=i-1; j>=0; --j )
                childs_.at(j)->finalizeEntry();
            finalize();

            return false;
        }
    }

    return true;
}

 // 解放の再帰的呼び出し
 // 初期化と逆順に処理を呼び出す。
void LevelNode::finalizeEntry()
{
    const size_t kChildNum = childs_.size();
    for( int i=kChildNum-1; i>=0; --i )
    {
        childs_.at(i)->finalizeEntry();
    }

    finalize();
}
