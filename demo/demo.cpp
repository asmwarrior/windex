
// include the header only windex gui framework
#include "wex.h"
#include "propertygrid.h"
#include "inputbox.h"
#include "plot2d.h"
#include "window2file.h"
using namespace wex;

void helloworld()
{
    // construct top level window
    gui& form = wex::windex::topWindow();
    form.move({ 50,50,400,400});
    form.text("Label and Editbox demo");

    // display labels
    label& lbA = wex::make<label>( form );
    lbA.move( {20, 20, 100, 30 } );
    lbA.text("A:");
    label& lbB = wex::make<label>( form );
    lbB.move( {20, 60, 100, 30 } );
    lbB.text("B:");

    // display textboxes
    editbox& edit1 = wex::make<editbox>( form );
    edit1.move( {80, 20, 100, 30 } );
    edit1.text( "type value");
    editbox& edit2 = wex::make<editbox>( form );
    edit2.move( {80, 60, 100, 30 } );
    edit2.text( "type value");

    // display a button
    button& btn = wex::make<button>( form );
    btn.move( {20, 100, 150, 30 } );
    btn.text( "Show values entered" );


    // popup a message box when button is clicked
    // showing the value entered in textbox
    btn.events().click([&]
    {
        std::string msg =
        "A is " + edit1.text() +
        ", B is " + edit2.text();
        msgbox(
            form,
            msg );
    });

    form.show();
}

void choiceDemo()
{
    // construct top level  window
    gui& form = wex::windex::topWindow();
    form.move({ 50,50,400,400});
    form.text("A windex combobox");

    // display combobox
    choice& cb = wex::make<choice>( form );
    cb.move(20, 50, 150, 130 );
    cb.add("Alpha");
    cb.add("Beta");
    cb.select(-1);
    cb.events().select( cb.id(), [&]
    {
        msgbox(
            form,
            cb.SelectedText() );
    });
    std::cout << "choice handle " << cb.handle()
              <<" "<< cb.id() << "\n";

    // display a button
    button& btn = wex::make<button>( form );
    btn.move( {20, 150, 150, 30 } );
    btn.text( "Show values selected" );
    btn.events().click([&]
    {
        msgbox(
            form,
            cb.SelectedText() );
    });

    form.show();
}

void drawDemo()
{

    // construct top level  window
    gui& form = wex::windex::topWindow();
    form.move({ 50,50,400,400});
    form.text("A windex draw demo");

    form.events().draw([]( PAINTSTRUCT& ps )
    {
        shapes S( ps );
        S.color( 255, 0, 0 );
        S.line( { 10,10, 50,50 } );
        S.color( 255,255,255 );
        S.rectangle( { 20,20,20,20});
        S.color( 255,255,0 );
        S.text( "test", {50,50,50,25} );
        S.color(0,0,255);
        S.circle( 100,100,40);
        S.arc( 100,100,30, 0, 90 );

        S.fill();
        S.rectangle(  { 200,20,20,20});
    });

    form.show();
}

void PGDemo()
{
    // construct top level window
    gui& form = wex::windex::topWindow();
    form.move({ 50,50,400,400});
    form.text("A windex property grid");

    // construct propertygrid
    propertyGrid& pg = wex::make<propertyGrid>( form );
    pg.move( { 10,10, 200, 200});
    pg.labelWidth( 50 );
    pg.bgcolor( 0xFFA0A0 );

    // add properties
    pg.category("Strings");
    pg.string( "A", "72" );
    pg.string( "B", "4600" );
    pg.string( "C", "72" );
    pg.string( "D", "4600" );
    pg.string( "E", "4600" );
    pg.string( "F", "4600" );
    pg.string( "G", "4600" );
    pg.string( "H", "4600" );
    pg.string( "I", "4600" );
    pg.string( "J", "4600" );
    pg.string( "K", "4600" );
    pg.string( "L", "4600" );
    pg.string( "M", "4600" );
    pg.string( "N", "4600" );
    pg.string( "O", "4600" );
    pg.expand("Strings",false);
    pg.category("Others");
    pg.choice( "Choose", { "X", "Y", "Z"} );
    pg.check( "Enable", false );

    form.events().resize([&](int w, int h)
    {
        // window containing propertyGrid has been resized
        // ensure that every visible label is completely redrawn
        pg.update();
    });

    // display a button
    button& btn = wex::make<button>( form );
    btn.move( {20, 250, 150, 30 } );
    btn.text( "Show values entered" );

    // popup a message box when button is clicked
    // showing the values entered
    btn.events().click([&]
    {
        std::string msg =
        "A is " + pg.value("A") +
        ", B is " + pg.value("B") +
        ", choice is " + pg.value("Choose") +
        ", enabled is ";
        if( pg.value("Enable") == "1" )
            msg += "true";
        else
            msg += "false";
        msgbox(
            form,
            msg );
    });

    pg.events().click([&]
    {
        msgbox( form, "pg click");
    });

    form.showModal();
}

void InputboxDemo()
{
    // construct top level window
    gui& form = wex::windex::topWindow();
    form.move({ 50,50,400,400});
    form.text("A windex inputbox");

    wex::inputbox ib( form );
    ib.add("A","72");
    ib.add("B","4600");
    ib.choice("Choose", { "X", "Y"} );
    ib.showModal();

    std::string msg =
        "A is " + ib.value("A") +
        ", B is " + ib.value("B") +
        ", choice is " + ib.value("Choose");
    msgbox(
        form,
        msg );

    // show the application
    form.show();

}
void RBDemo()
{
    // construct top level window
    gui& form = wex::windex::topWindow();
    form.move({ 50,50,400,400});
    form.text("A windex radiobutton");

    wex::groupbox& P = wex::make<wex::groupbox>( form );
    P.move( 5, 5, 350,350 );

    // use laypout to atomatically arrange buttons in columns
    wex::layout& L = wex::make<wex::layout>(P  );
    L.move( 50, 50,300,300);
    L.grid( 2 );                // specify 2 columns
    L.colfirst();               // specify column first order

    // first group of radiobuttons
    radiobutton& rb1 = wex::make<radiobutton>(L);
    rb1.first();                // first in group of interacting buttons
    rb1.move( {20,20,100,30} );
    rb1.text("Alpha");
    radiobutton& rb2 = wex::make<radiobutton>(L);
    rb2.move( {20,60,100,30} );
    rb2.text("Beta");
    radiobutton& rb3 = wex::make<radiobutton>(L);
    rb3.move( {20,100,100,30} );
    rb3.text("Gamma");

    // second group of radio buttons
    radiobutton& rb4 = wex::make<radiobutton>(L);
    rb4.first();                // first in group of interacting buttons
    rb4.size( 100,30 );
    rb4.text("X");
    radiobutton& rb5 = wex::make<radiobutton>(L);
    rb5.size( 100,30 );
    rb5.text("Y");
    radiobutton& rb6 = wex::make<radiobutton>(L);
    rb6.size( 100,30 );
    rb6.text("Z");

    // display a button
    button& btn = wex::make<button>( form );
    btn.move( {20, 150, 150, 30 } );
    btn.text( "Show values entered" );

    // popup a message box when button is clicked
    // showing the values entered
    btn.events().click([&]
    {
        std::string msg;
        if( rb1.isChecked() )
            msg = "Alpha";
        else if( rb2.isChecked() )
            msg = "Beta";
        else if( rb3.isChecked() )
            msg = "Gamma";
        else
            msg = "Nothing";
        msg += " is checked";
        msgbox(
            form,
            msg );
    });

    // show the application
    form.show();

}

void CBDemo()
{
    // construct top level window
    gui& form = wex::windex::topWindow();
    form.move({ 50,50,400,400});
    form.text("A windex checkbox");

    checkbox& rb1 = wex::make<checkbox>(form);
    rb1.move( {20,20,100,20} );
    rb1.text("Alpha");
    rb1.events().click([&]
    {
        if( rb1.isChecked() )
            msgbox( form, "Alpha clicked true") ;
        else
            msgbox( form, "Alpha clicked false") ;
    });
    checkbox& rb2 = wex::make<checkbox>(form);
    rb2.plus();
    rb2.move( {20,60,100,30} );
    rb2.text("Beta");
    checkbox& rb3 = wex::make<checkbox>(form);
    rb3.move( {20,100,100,30} );
    rb3.text("Gamma");

    // display a button
    button& btn = wex::make<button>( form );
    btn.move( {20, 150, 150, 30 } );
    btn.text( "Show values entered" );

    // popup a message box when button is clicked
    // showing the values entered
    btn.events().click([&]
    {
        std::string msg;
        if( rb1.isChecked() )
            msg += "Alpha ";
        if( rb2.isChecked() )
            msg += " Beta ";
        if( rb3.isChecked() )
            msg += " Gamma ";
        msg += " are checked";
        msgbox(
            form,
            msg );
    });

    // show the application
    form.show();

}

void PanelDemo()
{
    // construct top level window
    gui& form = wex::windex::topWindow();
    form.move({ 50,50,400,400});
    form.text("Panel demo");

    // construct panel
    groupbox& pnl = wex::make<groupbox>( form );
    pnl.move({ 100,100,200,200} );
    pnl.text("test");

    // display labels
    label& lbA = wex::make<label>( pnl );
    lbA.move( {20, 20, 50, 30 } );
    lbA.text("A:");
    label& lbB = wex::make<label>( pnl );
    lbB.move( {20, 60, 50, 30 } );
    lbB.text("B:");

    form.show();
}

void ScrollDemo()
{
    // construct top level window
    gui& form = wex::windex::topWindow();
    form.scroll();
    form.move({ 50,50,400,400});
    form.scrollRange(600,600);
    form.text("Scroll demo");

    // display labels
    label& lbA = wex::make<label>( form );
    lbA.move( {20, 20, 500, 30 } );
    lbA.text("AXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");
    label& lbB = wex::make<label>( form );
    lbB.move( {20, 460, 500, 30 } );
    lbB.text("BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB");;

    form.show();
}

void SliderDemo()
{
    // construct top level window
    gui& form = wex::windex::topWindow();
    form.move({ 50,50,500,400});
    form.text("Slider demo");

    // construct labels to display values when sliders are moved
    wex::label& label = wex::make<wex::label>(form);
    label.move( 200, 200, 100,30 );
    label.text("");
    wex::label& vlabel = wex::make<wex::label>(form);
    vlabel.move( 200, 240, 100,30 );
    vlabel.text("");

    // construct horizontal slider
    wex::slider& S = wex::make<wex::slider>( form );
    S.move({ 50,50,400,50});
    S.range( 0, 100 );
    S.text("horiz slider");
    S.events().slid([&](int pos)
    {
        label.text("horiz value: " + std::to_string( pos ));
        label.update();
    });

    // construct vertical slider
    wex::slider& V = wex::make<wex::slider>( form );
    V.move({ 50,100,50,400});
    V.range( 0, 10 );
    V.vertical();
    V.events().slid([&](int pos)
    {
        vlabel.text("vert value: " + std::to_string( pos ));
        vlabel.update();
    });

    form.show();
}

void MenuDemo()
{
    // construct top level window
    gui& form = wex::windex::topWindow();
    form.move({ 50,50,400,400});
    form.text("Menu demo");

    menubar mb( form );

    menu f( form );
    f.append("open",[&]
    {
        msgbox(form,"File open");
    });
    f.append("save");
    mb.append("File", f );
    menu e( form );
    e.append("change");
    mb.append("Edit", e );


//    int clicked = -1;
//
//    menu m;
//    m.append("test",[&]
//    {
//        clicked = 1;
//    });
//    m.append("second",[&]
//    {
//        clicked = 2;
//    });
//    m.append("third",[&]
//    {
//        clicked = 3;
//    });
//    m.popup( form, 200,200 );
//
//    msgbox( form,std::string("item ") + std::to_string(clicked) + " clicked");

    form.show();
}

void PlotDemo()
{
    wex::gui& fm = wex::windex::topWindow();
    fm.move( 50,50,1200,600 );

    // construct plot to be drawn on form
    wex::plot::plot& thePlot = wex::make<wex::plot::plot>( fm );
    thePlot.bgcolor( 0 );
    //thePlot.Grid( true );
    // resize plot when form resizes
    fm.events().resize([&](int w, int h )
    {
        thePlot.size( w-100, h-200 );
        thePlot.move( 30, 100 );
        thePlot.update();
    });

    wex::button& btnStatic = wex::make<wex::button>(fm);
    btnStatic.move(100,10,50,20);
    btnStatic.text("Static");
    btnStatic.events().click([&]
    {
        // construct plot traces
        wex::plot::trace& t1 = thePlot.AddStaticTrace();
        wex::plot::trace& t2 = thePlot.AddStaticTrace();

        // provide some data for first trace
        std::vector< double > d1 { 10, 15, 20, 25, 30, 25, 20, 15, 10 };
        t1.set( d1 );

        // plot in blue
        t1.color( 0x0000FF );

        // provide data for second trace
        std::vector< double > d2 { 20, 30, 40, 50, 60, 50, 40, 30, 20 };
        t2.set( d2 );

        // plot in red
        t2.color( 0xFF0000 );

        thePlot.update();
    });

    wex::button& btnScatter = wex::make<wex::button>(fm);
    btnScatter.move(200,10,50,20);
    btnScatter.text("Scatter");
    btnScatter.events().click([&]
    {
        std::vector< double > x { 0, 1, 2, 3, 4 };
        std::vector< double > y {  100, 50, -100, 50, 200 };
        plot::trace& t2 = thePlot.AddScatterTrace();
        t2.color( 0xFF0000 );
        for( int k = 0; k < (int)x.size(); k++ )
        {
            t2.add( 10 * x[k], y[k] );
        }
        thePlot.update();
    });

    wex::button& btnTime = wex::make<wex::button>(fm);
    btnTime.move(300,10,100,20);
    btnTime.text("Real Time");
    btnTime.events().click([&]
    {
        // construct plot trace
        // displaying 100 points before they scroll off the plot
        plot::trace& t1 = thePlot.AddRealTimeTrace( 100 );

        // plot in blue
        t1.color( 0xFF0000 );

        // create timer handler to provide new data regularly
        fm.events().timer([&]
        {
            static int p = 0;
            t1.add( 10 * sin( p++ / 10.0 ) );
            thePlot.update();
        });
        timer t( fm, 10 );
    });

    fm.show();
}

int main()
{

    // construct top level application window
    gui& form = wex::windex::topWindow();
    form.move({ 50,50,400,500});
    form.text("Windex demos");

    // construct layout to arrange buttons in a grid
    layout& l = wex::make<layout>( form );
    l.move( {20,20,400,400} );
    l.grid( 2 );

    // handle resize
    form.events().resize([&]( int w, int h )
    {
        l.size(w,h);
        l.update();
    });

    // display a button
    button& btnhello = wex::make<button>( l );
    btnhello.size( 150, 30 );
    btnhello.text( "Label and Editbox" );
    btnhello.events().click([]
    {
        helloworld();
    });
    button& btnchoice = wex::make<button>( l );
    btnchoice.size(  150, 30 );
    btnchoice.text( "Choice" );
    btnchoice.events().click([]
    {
        choiceDemo();
    });
    button& btnpg = wex::make<button>( l );
    btnpg.size(  150, 30 );
    btnpg.text( "Property Grid" );
    btnpg.events().click([]
    {
        PGDemo();
    });
    button& btnib = wex::make<button>( l );
    btnib.size(  150, 30 );
    btnib.text( "Inputbox" );
    btnib.events().click([]
    {
        InputboxDemo();
    });

    button& btnfb = wex::make<button>( l );
    btnfb.size(  150, 30 );
    btnfb.text( "Filebox" );
    btnfb.events().click([&]
    {
        filebox fb( form );
        msgbox( form,
                fb.path() );
    });

    button& btnrb = wex::make<button>( l );
    btnrb.size( 150, 30 );
    btnrb.text( "Radiobutton" );
    btnrb.events().click([&]
    {
        RBDemo();
    });

    button& btncb = wex::make<button>( l );
    btncb.size( 150, 30 );
    btncb.text( "Checkbox" );
    btncb.events().click([&]
    {
        CBDemo();
    });

    button& btnpanel =wex::make<button>( l );
    btnpanel.size( 150, 30 );
    btnpanel.text( "Panel" );
    btnpanel.events().click([&]
    {
        PanelDemo();
    });

    button& btndraw = wex::make<button>( l );
    btndraw.size( 150, 30 );
    btndraw.text( "Draw" );
    btndraw.events().click([&]
    {
        drawDemo();
    });

    button& btnscroll = wex::make<button>( l );
    btnscroll.size( 150, 30 );
    btnscroll.text( "Scroll" );
    btnscroll.events().click([&]
    {
        ScrollDemo();
    });

    button& btnmenu = wex::make<button>( l );
    btnmenu.size(  150, 30 );
    btnmenu.text( "Menu" );
    btnmenu.events().click([&]
    {
        MenuDemo();
    });

    button& btnplot = wex::make<button>( l );
    btnplot.size(  150, 30 );
    btnplot.text( "Plot" );
    btnplot.events().click([&]
    {
        PlotDemo();
    });

    button& btnslider = wex::make<button>( l );
    btnslider.size(  150, 30 );
    btnslider.text( "Slider" );
    btnslider.events().click([&]
    {
        SliderDemo();
    });

    button& btnpng = wex::make<button>( l );
    btnpng.size(  150, 30 );
    btnpng.text( "Save to demo.png" );
    btnpng.events().click([&]
    {
        window2file w2f;
        w2f.save( form, "demo.png" );
    });

    // show the application
    form.show();

    //Pass the control of the application to the windows message queue.
    //Blocks execution for dispatching user
    //input until the form is closed.

    form.run();

    return 0;
}
