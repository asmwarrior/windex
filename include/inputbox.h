#include "propertygrid.h"
namespace wex
{
class inputbox : public window
{
public:
    inputbox( window& parent )
        : myGrid( propertyGrid( *this ))
        , myOKButton( windex::get().make<button>(*this) )
    {
        windex::get().Add( this );
        text("inputbox");
        move({100,100,300,300});
        myGrid.move( { 50,50, 200, 30});
        myGrid.labelWidth( 50 );
        myGrid.bgcolor( 0xFFA0A0 );
        myOKButton.move( { 100,200, 50, 40 } );
        myOKButton.text("OK");
        myOKButton.events().click([this]
        {
            //std::cout << "destroying inputbox " << myHandle << "\n";

            // before destroying the window extract values from gui into property attributes
            myGrid.saveValues();

            myfModal = false;
            DestroyWindow(myHandle);
        });
    }
    void Add(
        const std::string& name,
        const std::string& def )
    {
        myGrid.string( name, def );
    }
//    void Show()
//    {
//
//    }

    void modal()
    {
        showModal();
    }
    /// get value saved in proprty attribute
    std::string value( const std::string& name )
    {
        auto p = myGrid.find( name );
        return p->savedValue();
    }
private:
    propertyGrid myGrid;
    button& myOKButton;
};
}