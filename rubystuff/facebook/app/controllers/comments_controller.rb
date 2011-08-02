class CommentsController < ApplicationController
 def index
    @comments = Comment.all

    respond_to do |format|
      format.html # index.html.erb
      format.xml  { render :xml => @comments }
    end
  end

  # GET /posts/1
  # GET /posts/1.xml
  def show
    @comment = Comment.find(params[:id])
    
    respond_to do |format|
      format.html # show.html.erb
      format.xml  { render :xml => @comment }
    end
  end

  # GET /posts/new
  # GET /posts/new.xml
  def new
    @comment = Comment.new

    respond_to do |format|
      format.html # new.html.erb
      format.xml  { render :xml => @comment }
    end
  end

  # GET /posts/1/edit
  def edit
    @comment = Comment.find(params[:id])
  end

  # POST /posts
  # POST /posts.xml
  def create
    @comment = Comment.new(params[:comment])
  if @comment.valid?
     respond_to do |format|
      @comment.save
        format.html { redirect_to(@comment, :notice => 'Post was successfully created.') }
        format.xml  { render :xml => @comment, :status => :created, :location => @comment }
         end
      else
      respond_to do |format|
        format.html { render :action => "new" }
        format.xml  { render :xml => @comment.errors, :status => :unprocessable_entity }
          end
    end
  end

  # PUT /posts/1
  # PUT /posts/1.xml
  def update
    @comment = Comment.find(params[:id])

    respond_to do |format|
      if @comment.update_attributes(params[:comment])
        format.html { redirect_to(@comment, :notice => 'comment was successfully updated.') }
        format.xml  { head :ok }
      else
        format.html { render :action => "edit" }
        format.xml  { render :xml => @comment.errors, :status => :unprocessable_entity }
      end
    end
  end

  # DELETE /posts/1
  # DELETE /posts/1.xml
  def destroy
    @comment = Comment.find(params[:id])
    @comment.destroy

    respond_to do |format|
      format.html { redirect_to(comments_url) }
      format.xml  { head :ok }
    end
  end

end
