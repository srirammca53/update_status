class GooglesController < ApplicationController
  # GET /googles
  # GET /googles.xml
  def index
    @googles = Google.all

    respond_to do |format|
      format.html # index.html.erb
      format.xml  { render :xml => @googles }
    end
  end

  # GET /googles/1
  # GET /googles/1.xml
  def show
    @google = Google.find(params[:id])

    respond_to do |format|
      format.html # show.html.erb
      format.xml  { render :xml => @google }
    end
  end

  # GET /googles/new
  # GET /googles/new.xml
  def new
    @google = Google.new

    respond_to do |format|
      format.html # new.html.erb
      format.xml  { render :xml => @google }
    end
  end

  # GET /googles/1/edit
  def edit
    @google = Google.find(params[:id])
  end

  # POST /googles
  # POST /googles.xml
  def create
    @google = Google.new(params[:google])

    respond_to do |format|
      if @google.save
        format.html { redirect_to(@google, :notice => 'Google was successfully created.') }
        format.xml  { render :xml => @google, :status => :created, :location => @google }
      else
        format.html { render :action => "new" }
        format.xml  { render :xml => @google.errors, :status => :unprocessable_entity }
      end
    end
  end

  # PUT /googles/1
  # PUT /googles/1.xml
  def update
    @google = Google.find(params[:id])

    respond_to do |format|
      if @google.update_attributes(params[:google])
        format.html { redirect_to(@google, :notice => 'Google was successfully updated.') }
        format.xml  { head :ok }
      else
        format.html { render :action => "edit" }
        format.xml  { render :xml => @google.errors, :status => :unprocessable_entity }
      end
    end
  end

  # DELETE /googles/1
  # DELETE /googles/1.xml
  def destroy
    @google = Google.find(params[:id])
    @google.destroy

    respond_to do |format|
      format.html { redirect_to(googles_url) }
      format.xml  { head :ok }
    end
  end
end
