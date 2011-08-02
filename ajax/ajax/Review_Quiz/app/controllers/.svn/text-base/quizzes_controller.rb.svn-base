class QuizzesController < ApplicationController
  
  before_filter :find_quiz, :except => [ :index, :create ]
  before_filter :check_permissions, :only => [ :edit, :reorder, :questions, :destroy_question ]

  def index
    @quizzes = Quiz.recent
  end
  
  # Creates a new quiz and saves the user's session id in it
  def create
    quiz = Quiz.new params[:new_quiz]
    quiz.session_id = session.session_id
    quiz.save
    redirect_to edit_quiz_url(:id => quiz)
  end
  
  def edit
  end

  # Creates a new question, via either Ajax or traditional form
  def create_q
    @question = @quiz.questions.create params[:question]
    respond_to do |format|
      format.html { redirect_to edit_quiz_url }
      format.js
    end
  end

  # Handles drag-and-drop reordering questions via Ajax
  def reorder
    params[:quiz].each_with_index do |id, position|
      q = @quiz.questions.find id
      q.position = position + 1
      q.save
    end
    render :nothing => true
  end

  # Handles deleting a question via Ajax
  def destroy_q
    question = @quiz.questions.find params[:question_id]
    question.destroy
    render :nothing => true
  end

  # Shows the first five unmissed questions
  def show
    @questions = @quiz.questions.unmissed right_keys
  end
  
  # Returns a response to a question via Ajax
  def answer
    score @quiz.id, params[:question_id], params[:right]=='true'
    last = @quiz.questions.find params[:last]
    @next = last.next right_keys
  end

  # Resets the user's scoreboard for the quiz
  def reset
    reset_scoreboard params[:id]
    redirect_to quiz_url
  end
  
  private
  
    def find_quiz() @quiz = Quiz.find params[:id] end
    
    # Before filter to ensure only a quiz's creator can edit it
    def check_permissions
      redirect_to home_url and return false unless mine?
    end
    
    # Whether @quiz was created by the user
    def mine?
      @quiz.session_id == session.session_id
    end
    helper_method :mine?

    # Wraps session to track user's quiz results
    def scoreboard id=nil
      return (session[:quizzes] ||= {}) unless id
      return (scoreboard[id.to_i] ||= {})
    end

    # Wipes the user's scoreboard for a given quiz
    def reset_scoreboard id
      scoreboard[id.to_i] = {}
    end

    # A response (+right+) for question +q+ of quiz +quiz+
    def score id, q, right
      scoreboard(id)[q.to_i] = right
    end

    # An array of hashes representing right answers for quiz +id+
    def right(id) scoreboard(id).reject{ |q, v| !v } end
    helper_method :right

    # An array of hashes representing wrong answers for quiz +id+
    def wrong(id) scoreboard(id).reject{ |q, v| v } end
    helper_method :wrong
    
    # A comma-delimited string of ids to the right responses for the current quiz.
    def right_keys
      questions = right(@quiz.id)
      questions.keys.join ','
    end

end
