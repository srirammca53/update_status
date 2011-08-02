class PaintersController < ApplicationController
  # GET /painters
  # GET /painters.xml
  def index
    @painters = Painter.all

    respond_to do |format|
      format.html # index.html.erb
      format.xml  { render :xml => @painters }
    end
  end

  # GET /painters/1
  # GET /painters/1.xml
  def show
    @painter = Painter.find(params[:id])

    respond_to do |format|
      format.html # show.html.erb
      format.xml  { render :xml => @painter }
    end
  end

  # GET /painters/new
  # GET /painters/new.xml
  def new
    @painter = Painter.new

    respond_to do |format|
      format.html # new.html.erb
      format.xml  { render :xml => @painter }
    end
  end

  # GET /painters/1/edit
  def edit
    @painter = Painter.find(params[:id])
  end

  # POST /painters
  # POST /painters.xml
  def create
    @painter = Painter.new(params[:painter])

    respond_to do |format|
      if @painter.save
        format.html { redirect_to(@painter, :notice => 'Painter was successfully created.') }
        format.xml  { render :xml => @painter, :status => :created, :location => @painter }
      else
        format.html { render :action => "new" }
        format.xml  { render :xml => @painter.errors, :status => :unprocessable_entity }
      end
    end
  end

  # PUT /painters/1
  # PUT /painters/1.xml
  def update
    @painter = Painter.find(params[:id])

    respond_to do |format|
      if @painter.update_attributes(params[:painter])
        format.html { redirect_to(@painter, :notice => 'Painter was successfully updated.') }
        format.xml  { head :ok }
      else
        format.html { render :action => "edit" }
        format.xml  { render :xml => @painter.errors, :status => :unprocessable_entity }
      end
    end
  end

  # DELETE /painters/1
  # DELETE /painters/1.xml
  def destroy
    @painter = Painter.find(params[:id])
    @painter.destroy

    respond_to do |format|
      format.html { redirect_to(painters_url) }
      format.xml  { head :ok }
    end
  end
end
