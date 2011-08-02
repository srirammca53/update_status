class CreditController < ApplicationController
def create
    @account = Account.find(params[:account_id])
    @credit = @account.credit.create(params[:credit])
    redirect_to credit_path(@credit)
  end
 def new
    @credit = Credit.new
@credit = @account.credit.create(params[:credit])
   redirect_to credit_path(@credit)
  end
def show
    @account = Account.find(params[:id])
      redirect_to accounts_path(@credit)
    end

end
