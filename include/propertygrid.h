#pragma once
#include "wex.h"
namespace wex
{
class propertyGrid;

/// A name value pair
class property
{
public:
    property(
        gui* parent,
        const std::string& name,
        const std::string& value )
        : myName( name )
        , myValue( value )
        , W( windex::get())
        , myLabel( wex::maker::make<label>(*parent) )
        , myEditbox( wex::maker::make<editbox>(*parent) )
        , myCombobox( wex::maker::make<choice>(*parent) )
        , myCheckbox( wex::maker::make<checkbox>(*parent) )
        , myCategoryExpanded( wex::maker::make<checkbox>(*parent) )
        , myLabelWidth( 100 )
        , myType( eType::string )
    {
        myLabel.text( myName );
        myEditbox.text( myValue );

    }
    property(
        gui* parent,
        const std::string& name,
        bool value )
        : myName( name )
        , myValue( std::to_string((int)value ))
        , W( windex::get())
        , myLabel( wex::maker::make<label>(*parent) )
        , myEditbox( wex::maker::make<editbox>(*parent) )
        , myCombobox( wex::maker::make<choice>(*parent) )
        , myCheckbox( wex::maker::make<checkbox>(*parent) )
        , myCategoryExpanded( wex::maker::make<checkbox>(*parent) )
        , myLabelWidth( 100 )
        , myType( eType::check )
    {
        myLabel.text( myName );
        myCheckbox.check( value );
        myCheckbox.text("");
        myCheckbox.events().clickPropogate();
    }
    property(
        gui* parent,
        const std::string& name,
        const std::vector< std::string >& value )
        : myName( name )
        , myValue( "" )
        , W( windex::get())
        , myLabel( wex::maker::make<label>(*parent) )
        , myEditbox( wex::maker::make<editbox>(*parent) )
        , myCombobox( wex::maker::make<choice>(*parent) )
        , myCheckbox( wex::maker::make<checkbox>(*parent) )
        , myCategoryExpanded( wex::maker::make<checkbox>(*parent) )
        , myLabelWidth( 100 )
        , myType( eType::choice )
    {
        myLabel.text( myName );
        for( auto& t : value )
        {
            myCombobox.add( t );
        }
    }
    /// construct a category
    property(
        gui* parent,
        const std::string& name )
        : myName( name )
        , W( windex::get())
        , myLabel( wex::maker::make<label>(*parent) )
        , myEditbox( wex::maker::make<editbox>(*parent) )
        , myCombobox( wex::maker::make<choice>(*parent) )
        , myCheckbox( wex::maker::make<checkbox>(*parent) )
        , myCategoryExpanded( wex::maker::make<checkbox>(*parent) )
        , myType( eType::category )
    {
        myCategoryExpanded.text( myName );
        myCategoryExpanded.plus();
        myCategoryExpanded.check();
        myCategoryExpanded.events().clickPropogate();
    }
    void move( const std::vector<int>& r )
    {
        std::vector<int> rl( r );
        rl[2] = myLabelWidth;
        myLabel.move( rl );

        std::vector<int> re( r );
        re[0] += myLabelWidth;
        re[2] -= myLabelWidth;
        switch( myType )
        {
        case eType::string:
            myCategoryExpanded.move({0,0,0,0});
            myEditbox.move( re );
            break;
        case eType::choice:
            re[3] *= myCombobox.count();
            myCombobox.move( re[0], re[1], re[2], re[3] );
            break;
        case eType::check:
            myCheckbox.move( re );
            break;
        case eType::category:
            re = r;
            re[1] += 0.5 * re[3];
            re[3] /= 2;
            myCategoryExpanded.move( re );
            myLabel.move({0,0,0,0});        // keep unused label out of the way
            break;
        }
    }
    void labelWidth( int w )
    {
        myLabelWidth = w;
    }
    void bgcolor( int color )
    {
        myLabel.bgcolor( color );
    }
    /** Add pop help message when mouse hovers over property label
        @param[in] tip the help message
        @return property reference
    */
    property& tooltip( const std::string& tip )
    {
        myLabel.tooltip( tip );
        return *this;
    }
    /** Set property to be readonly
        @param[in] f true if property should be readonly, default true
        @return property reference

        A property defaults to editable when constructed.
    */
    property& readonly( bool f = true )
    {
        switch( myType )
        {
        case eType::string:
            myEditbox.readonly( f );
            break;
        default:
            break;
        }
        return *this;
    }
    void show( bool f = true )
    {
        myLabel.show( f );
        switch( myType )
        {
        case eType::string:
            myEditbox.show( f );
            break;
        case eType::choice:
            myCombobox.show( f );
            break;
        case eType::check:
            myCheckbox.show( f );
            break;
        case eType::category:
            myLabel.show( false );        // keep unused label out of the way
            myCategoryExpanded.show( f );
            break;
        }
    }
    /** Update ( redraw ) property child widgets

    Some widgets update nicely when the window containing the property grid resizes
    Others, most significantly labels, do not.  So application code should
    handle containing window resizes by calling propertyGrid::update()
    which will call this method on all properties.
    */
    void update()
    {
        myLabel.update();
        myCheckbox.update();
        myCategoryExpanded.update();
    }

    const std::string& name() const
    {
        return myName;
    }
    const std::string value() const
    {
        switch( myType )
        {
        case eType::string:
            return myEditbox.text();

        case eType::choice:
            return myCombobox.SelectedText();

        case eType::check:
            return std::to_string( (int) myCheckbox.isChecked() );
            break;

        case eType::category:
            break;
        }
        return std::string("");
    }
    /// set property value
    void value( const std::string v )
    {
        switch( myType )
        {
        case eType::string:
            myValue = v;
            myEditbox.text( v );
            myEditbox.update();
            break;
        case eType::choice:
            myValue = v;
            myCombobox.select( v );
            break;
        default:
            break;
        }
    }
    void value_bool( bool v )
    {
        switch( myType )
        {
        case eType::check:
            myValue = std::to_string((int)v );
            myCheckbox.check( v );
            break;
        default:
            // other property types ignore requests to change boolean vaue
            break;
        }
    }
    /// copy value from gui into myValue attribute
    void saveValue()
    {
        switch( myType )
        {
        case eType::string:
            myValue = myEditbox.text();
            break;
        case eType::choice:
            myValue = myCombobox.SelectedText();
            break;
        case eType::check:
            myValue = std::to_string( (int) myCheckbox.isChecked() );
            break;
        case eType::category:
            break;
        }
    }

    // get myValue attribute
    const std::string savedValue() const
    {
        return myValue;
    }

    bool isCategory() const
    {
        return myType == eType::category;
    }
    bool isExpanded() const
    {
        if( ! isCategory() )
            return false;
        return myCategoryExpanded.isChecked();
    }
    void expand( bool f )
    {
        myCategoryExpanded.check( f );
    }
    /// register function to call when property value changes
    void change( std::function<void()> f )
    {
        switch( myType )
        {
        case eType::string:
            myEditbox.events().change( myEditbox.id(), f );
            break;
        case eType::check:
            myCheckbox.events().click( f );
            break;
        default:
            break;
        }
    }
private:
    std::string myName;
    std::string myValue;
    wex::windex& W;
    wex::label& myLabel;
    wex::editbox& myEditbox;
    wex::choice& myCombobox;
    wex::checkbox& myCheckbox;
    wex::checkbox& myCategoryExpanded;
    int myLabelWidth;
    enum class eType
    {
        string,
        choice,
        check,
        category
    }
    myType;
};
/// A grid of properties
class propertyGrid : public gui
{
public:
    propertyGrid( gui* parent )
        : gui( parent )
        , myHeight( 25 )
        , myWidth( 300 )
        , myLabelWidth( 100 )
        , myBGColor( 0xc8c8c8)
        , myfScroll( false )
    {
        text("PG");

        // default event handlers
        events().click([this]
        {
            visible();
        });
        change( []
        {

        });
    }
    /** Add string property
        @param[in] name of property
        @param[in] value initial value
        @return reference to property
    */
    property& string(
        const std::string& name,
        const std::string& value )
    {
        property P( this, name, value );
        CommonConstruction( P );
        return myProperty.back();
    }
    /** Add choice property
        @param[in] name of property
        @param[in] choice vector of choices to be selected from
        @return reference to property
    */
    property& choice(
        const std::string& name,
        const std::vector< std::string >& choice )
    {
        property P( this, name, choice );
        CommonConstruction( P );
        return myProperty.back();
    }
    /// Add boolean property
    void check(
        const std::string& name,
        bool f )
    {
        property P( this, name, f );
        CommonConstruction( P );
    }
    /// Add categoty
    void category(
        const std::string& name )
    {
        property P( this, name );
        CommonConstruction( P );
    }
    /// Add scrollbars
    void scroll()
    {
        myfScroll = true;
        gui::scroll();
    }
    /// Expand, or contract, category of properties
    void expand(
        const std::string name,
        bool fexpand = true )
    {
        for( auto& p : myProperty )
        {
            if( p.name() == name &&
                    p.isCategory() )
            {
                p.expand( fexpand );
                visible();
                return;
            }
        }
    }
    void move( const std::vector<int>& r )
    {
        gui::move( r );
        myWidth = r[2];
    }
    void labelWidth( int w )
    {
        myLabelWidth = w;
    }

    /// force every property to redraw its label
    void update()
    {
        for( auto& p : myProperty )
            p.update();
        gui::update();
    }

    /// get pointer to first property with name, ignoring categories
    property* find( const std::string& name )
    {
        for( auto& p : myProperty )
        {
            //std::cout << "property::find " << name <<" "<< p.name() << "\n";
            if( p.name() == name )
                return &p;
        }
        return nullptr;
    }

    /// get pointer to first property with name in a category
    property* find(
        const std::string& category,
        const std::string& name)
    {
        for( auto p = myProperty.begin();
                p != myProperty.end();
                p++ )
        {
            if( p->isCategory() )
            {
                if( p->name() == category )
                {
                    for( p++;
                            p != myProperty.end();
                            p++ )
                    {
                        if( p->isCategory() )
                            return nullptr;
                        if( p->name() == name)
                            return &(*p);
                    }
                }
            }
        }
        return nullptr;
    }

    /// get value in editbox of property with name
    const std::string value( const std::string& name )
    {
        std::cout << "PG value " << name << "\n";
        property* p = find( name );
        if( ! p )
        {
            static std::string null;
            return null;
        }
        std::string v = p->value();
        return p->value();
    }

    /// save values in all property textboxes in the property's myValue attribute
    void saveValues()
    {
        for( auto& p : myProperty )
        {
            p.saveValue();
        }
    }

    int propHeight() const
    {
        return myHeight;
    }
    int width() const
    {
        return myWidth;
    }
    int propCount() const
    {
        return (int) myProperty.size();
    }
    /// Register function to call when property value has changed
    void change( std::function<void()> f )
    {
        onChange = f;
    }
private:
    std::vector< property > myProperty;     // the properties in the grid
    int myHeight;                           // height of a single property
    int myWidth;                            // width of grid
    int myLabelWidth;                       // width of property labels
    int myBGColor;                          // grid background color
    bool myfScroll;                         // true if scrollbars used
    std::function<void()> onChange;         // funtion to call when property has changed

    void CommonConstruction( property& P )
    {
        P.labelWidth( myLabelWidth );
        P.bgcolor( myBGColor );
        myProperty.push_back( P );

        if( myfScroll )
            scrollRange(
                myWidth,
                ((int)myProperty.size()+1) * myHeight);

        visible();

        P.change( [this]
        {
            onChange();
        });
    }
    /** Show properties when category is expanded or collapsed
    */
    void visible(  )
    {
        // hide all the properties
        for( auto& P : myProperty)
            P.show( false );

        // show properties in expanded categories
        bool expanded = true;       /// true if current category is expanded
        int index = 0;              /// number of property heights displayed so far
        for( auto& P : myProperty)
        {
            if( P.isCategory() )
            {
                //std::cout << "cat " << P.name()  << " at " << index << "\n";
                P.move( { 0, index * myHeight, myWidth, 2 * myHeight } );     // category always visible
                P.show();
                index += 2;             // display takes two rows
                expanded = P.isExpanded();       // control visibility of contained properties
            }
            else if( expanded )
            {
                //std::cout << "show " << P.name() <<" at "<< index << "\n";
                P.move( { 0, index * myHeight, myWidth, myHeight } );     // property is visible
                P.show();
                index++;                // displays in one row
            }
            else
            {
                //std::cout << "hide " << P.name() << "\n";
                P.move( { 0,0,0,0 });    // invisible property
                P.show( false );
            }
        }
        if( myfScroll )
            scrollRange(
                myWidth,
                index * myHeight);
        update();
    }
};
}
