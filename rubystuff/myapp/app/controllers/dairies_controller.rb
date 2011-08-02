class DairiesController < ApplicationController
  # GET /dairies
  # GET /dairies.xml
  def index
    @dairies = Dairy.all

    respond_to do |format|
      format.html # index.html.erb
      format.xml  { render :xml => @dairies }
    end
  end

  # GET /dairies/1
  # GET /dairies/1.xml
  def show
    @dairy = Dairy.find(params[:id])

    respond_to do |format|
      format.html # show.html.erb
      format.xml  { render :xml => @dairy }
    end
  end

  # GET /dairies/new
  # GET /dairies/new.xml
  def new
    @dairy = Dairy.new

    respond_to do |format|
      format.html # new.html.erb
      format.xml  { render :xml => @dairy }
    end
  end

  # GET /dairies/1/edit
  def edit
    @dairy = Dairy.find(params[:id])
  end

  # POST /dairies
  # POST /dairies.xml
  def create
    @dairy = Dairy.new(params[:dairy])

    respond_to do |format|
      if @dairy.save
        format.html { redirect_to(@dairy, :notice => 'Dairy was successfully created.') }
        format.xml  { render :xml => @dairy, :status => :created, :location => @dairy }
      else
        format.html { render :action => "new" }
        format.xml  { render :xml => @dairy.errors, :status => :unprocessable_entity }
      end
    end
  end

  # PUT /dairies/1
  # PUT /dairies/1.xml
  def update
    @dairy = Dairy.find(params[:id])

    respond_to do |format|
      if @dairy.update_attributes(params[:dairy])
        format.html { redirect_to(@dairy, :notice => 'Dairy was successfully updated.') }
        format.xml  { head :ok }
      else
        format.html { render :action => "edit" }
        format.xml  { render :xml => @dairy.errors, :status => :unprocessable_entity }
      end
    end
  end

  # DELETE /dairies/1
  # DELETE /dairies/1.xml
  def destroy
    @dairy = Dairy.find(params[:id])
    @dairy.destroy

    respond_to do |format|
      format.html { redirect_to(dairies_url) }
      format.xml  { head :ok }
    end
  end
end
